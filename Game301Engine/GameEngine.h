//Andrew Puntillo
//---
//Engine Core Class:
//This class serves as the engine core initializing the window, the game interface, and the scene.
//Can only be initialized as a Singleton.
//---

#pragma once
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Window.h"
#include "GameInterface.h"
#include "LogManager.h"
#include "Timer.h"
#include "SceneGraph.h"
#include "Camera.h"
#include "InputManager.h"

namespace ENGINE
{

	class GameEngine
	{
	public:
		~GameEngine();

		//Get the instance of the engine
		static GameEngine* getInstance();
		
		bool onStart(); //Initialize
		static void onEnd(); //Terminate

		void run();
		void processInput();
		void update();
		void preRender();
		void render();
		void postRender();
		void logMessage();

		//Getters
		Window* getWindow() const { return m_window; };
		SceneGraph* getSceneGraph() { return m_sceneGraph; };
		Camera* getCamera() { return m_camera; }
		InputManager* getInputManager() { return m_inputManager; }

		//This is the pointer to the abstract Game/DemoApp
		GameInterface* gameInterface = nullptr;

	private:
		//Private for singleton purposes
		GameEngine();

		static GameEngine* m_gameEngineInstance;
		static Window* m_window;

		SceneGraph* m_sceneGraph;
		Camera* m_camera;

		bool m_isRunning = false;

		InputManager* m_inputManager;
	};

}

#endif