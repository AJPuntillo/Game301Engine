#include "Mesh.h"

using namespace ENGINE;

//Triangle
//float vertices[] = {
//	 0.0,  0.5, 0.0,
//	-0.5, -0.5, 0.0,
//	 0.5, -0.5, 0.0
//};

//Cube
float vertices[] = {
	// positions         // texture coords
	0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
	0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
   -0.5f,  0.5f, 0.0f,   0.0f, 1.0f, // top left 
    0.5f,  0.5f, 0.0f,   1.0f, 1.0f // top right
};

Mesh::Mesh()
{
	//Setup vertex
	vertexDescriptor = new VertexDescriptor();
	vertexDescriptor->addComponent(VertexComponentDescriptor::VertexComponentType::VC_POSITION_3F);
	vertexDescriptor->addComponent(VertexComponentDescriptor::VertexComponentType::VC_TEXCOORDS_2F);
	
	setupMesh();
}

void Mesh::render()
{
	//Draw mesh
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Mesh::setupMesh()
{
	//Generate buffers
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	
	//Bind the VAO
	glBindVertexArray(m_VAO);

	//Bind and populate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Generate attributes based on vertex descriptor
	for (int i = 0; i < vertexDescriptor->getSize(); i++) {
		glVertexAttribPointer(i, vertexDescriptor->componentList[i].getNumFloats(), GL_FLOAT, GL_FALSE, vertexDescriptor->stride * sizeof(float), (void*)(vertexDescriptor->componentList[i].offset * sizeof(float)));
		glEnableVertexAttribArray(i);
	}

	//Debugging
	std::cout << vertexDescriptor->stride * sizeof(float) << std::endl;

	//You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	//VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

unsigned int Mesh::loadTexture(ImageManager::HandleType imageHandle_)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	if (ImageManager::getInstance()->getImage(imageHandle_)->getImage())
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, ImageManager::getInstance()->getImage(imageHandle_)->getFormat(),
			ImageManager::getInstance()->getImage(imageHandle_)->getWidth(),
			ImageManager::getInstance()->getImage(imageHandle_)->getHeight(),
			0,
			ImageManager::getInstance()->getImage(imageHandle_)->getFormat(),
			GL_UNSIGNED_BYTE,
			ImageManager::getInstance()->getImage(imageHandle_)->getImage());
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ImageManager::getInstance()->getImage(imageHandle_)->getFormat() == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); //Depending on the format, choose repeat or clamp to edge
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ImageManager::getInstance()->getImage(imageHandle_)->getFormat() == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//stbi_set_flip_vertically_on_load(true); //Flippy

		stbi_image_free(ImageManager::getInstance()->getImage(imageHandle_)->getImage());
	}
	else
	{
		std::cout << "Texture failed to load" << std::endl;
		stbi_image_free(ImageManager::getInstance()->getImage(imageHandle_)->getImage());
	}
	glBindTexture(GL_TEXTURE_2D, 0); //As a precaution, unbind the texture after it has been created
	return textureID;
}