#include "Mesh.h"

using namespace ENGINE;

float vertices[] = {
	 0.0,  0.5, 0.0,
	-0.5, -0.5, 0.0,
	 0.5, -0.5, 0.0
};

Mesh::Mesh()
{
	//Setup vertex
	vertexDescriptor = new VertexDescriptor();
	vertexDescriptor->addComponent(VertexComponentDescriptor::VertexComponentType::VC_POSITION_3F);
	//vertexDescriptor->addComponent(VertexComponentDescriptor::VertexComponentType::VC_NORMALS_3F);
	
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