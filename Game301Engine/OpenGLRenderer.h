//Andrew Puntillo
//---
//OpenGL Renderer Class:
//The renderer class that inherits from the Abtract Renderer. Has a specific shape to be rendered.
//---

#pragma once
#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "AbstractRenderer.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "Vertex.h"

namespace ENGINE
{

	class OpenGLRenderer : AbstractRenderer
	{
	public:
		OpenGLRenderer();
		virtual ~OpenGLRenderer();

		virtual void renderPrimitive();

	private:
		GLuint m_VAO, m_VBO;
		Shader* triangleShader;
		Mesh* triangleMesh;
		VertexDescriptor* vertexDescriptor;

		ResourceManager<Mesh>* manager;
		ResourceHandle<Mesh> handle;
	};

}

#endif