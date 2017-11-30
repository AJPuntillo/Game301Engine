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
#include "ImageManager.h"

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
		unsigned int loadTexture(ImageManager::HandleType imageHandle_);

		//Vertex Data
		VertexDescriptor* vertexDescriptor;

	private:
		void setupMesh();

		//Render data
		GLuint m_VBO, m_VAO;
	};

}
#endif