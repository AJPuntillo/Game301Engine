//Andrew Puntillo
//---
//Game Interface Class:
//This class serves as the "scene manager". It contains the game as a whole while managing the input and scenes to be switched.
//This is an interface that need its methods overriden.
//---

#pragma once
#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

namespace ENGINE {

	//Interface Class
	class GameInterface
	{
	public:
		GameInterface() {};
		virtual ~GameInterface() {};

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