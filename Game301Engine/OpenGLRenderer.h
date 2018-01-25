//Andrew Puntillo
//---
//OpenGL Renderer Class:
//The renderer class that inherits from the Abtract Renderer. Has a specific shape to be rendered.
//---

#pragma once
#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "AbstractRenderer.h"
#include "GameObject.h"
#include "ModelManager.h"
#include "EffectedModel.h"
#include "Vertex.h"
#include "Window.h"
#include "MatrixStack.h"
#include "ModelLoader.h"

namespace ENGINE
{

	class OpenGLRenderer : AbstractRenderer
	{
	public:
		OpenGLRenderer();
		virtual ~OpenGLRenderer();

		void render(GameObject* obj_);
		void renderSceneGraph(SceneNode* rootNode_);
		void renderSceneNode(SceneNode* sceneNode_);
		
		//Post/Pre render calls
		void clearBuffers(glm::vec4 clearColour_ = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f)); //Optional clear colour
		void swapBuffers(Window* window_);


	private:
		MatrixStack matStk;
	};

}

#endif