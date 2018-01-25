//Andrew Puntillo
//---
//Scene Interface Class:
//Similar to the Game Interface class, the Scene Interface manage specifically everything in the scene.
//Interface class with methods required to be overriden.
//---

#pragma once
#ifndef SCENEINTERFACE_H
#define SCENEINTERFACE_H

#include "GameEngine.h"

namespace ENGINE {

	//Interface Class
	class SceneInterface
	{
	public:
		SceneInterface() {};
		virtual ~SceneInterface() {};

		//By saying virtual and = 0 we delete the method and force the inherited classes to create these and flush them out
		virtual bool onStart() = 0;
		virtual void onEnd() = 0;
		virtual void processInput() = 0;
		virtual void update() = 0;
		virtual void preRender() = 0;
		virtual void render() = 0;
		virtual void postRender() = 0;
		virtual void logMessage() = 0;
	};

}

#endif