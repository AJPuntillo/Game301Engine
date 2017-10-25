//Andrew Puntillo
//---
//OpenGL Renderer Class:
//The renderer class that inherits from the Abtract Renderer. Has a specific shape to be rendered.
//---

#pragma once
#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "ResourceManager.h"
#include "Mesh.h"
#include "Vertex.h"

namespace ENGINE
{

	class OpenGLRenderer
	{
	public:
		OpenGLRenderer();
		~OpenGLRenderer();

		void renderPrimitive(ResourceHandle<Shader> shader, ResourceHandle<Mesh> mesh);

		//Getters
		ResourceManager<Mesh>* getMeshManager() { return meshManager; }
		ResourceManager<Shader>* getShaderManager() { return shaderManager; }

	private:
		//Resource Managers
		ResourceManager<Mesh>* meshManager;
		ResourceManager<Shader>* shaderManager;
	};

}

#endif