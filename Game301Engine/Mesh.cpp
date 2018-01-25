#include "Mesh.h"

using namespace ENGINE;

//Triangle
//float vertices[] = {
//	 0.0,  0.5, 0.0,
//	-0.5, -0.5, 0.0,
//	 0.5, -0.5, 0.0
//};

//Plane
//float vertices[] = {
//	// positions         // texture coords
//	0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
//	0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
//   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
//   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
//   -0.5f,  0.5f, 0.0f,   0.0f, 1.0f, // top left 
//    0.5f,  0.5f, 0.0f,   1.0f, 1.0f // top right
//};

Mesh::Mesh()
{
	//Setup vertices
	verts = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

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
	glDrawArrays(GL_TRIANGLES, 0, verts.size() * sizeof(float));
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
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), &verts[0], GL_STATIC_DRAW);

	//Generate attributes based on vertex descriptor
	for (int i = 0; i < vertexDescriptor->getSize(); i++) {
		glVertexAttribPointer(i, vertexDescriptor->componentList[i].getNumFloats(), GL_FLOAT, GL_FALSE, vertexDescriptor->stride * sizeof(float), (void*)(vertexDescriptor->componentList[i].offset * sizeof(float)));
		glEnableVertexAttribArray(i);
	}

	//Debugging
	//std::cout << vertexDescriptor->stride * sizeof(float) << std::endl;

	//You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	//VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}