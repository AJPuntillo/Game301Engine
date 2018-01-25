//Andrew Puntillo
//---
//Mesh Class:
//The Mesh takes in the model's vertices passed in by the Renderer.
//Sets up VAOs/VBOs and appropriate attributes based on the specified components in the VertexDescriptor.
//---

#pragma once
#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Vertex.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace ENGINE {

	class Mesh
	{
	public:
		Mesh();

		void render();

		//Vertex Data
		VertexDescriptor* vertexDescriptor;

		//Getters
		std::vector<float> getVertices() { return verts; }

	private:
		void setupMesh();

		//Render data
		GLuint m_VBO, m_VAO;
		std::vector<float> verts;
	};

}
#endif