#include "GameEngine.h"

using namespace ENGINE;

//Initialize static variables
GameEngine* GameEngine::m_gameEngineInstance = nullptr;
Window* GameEngine::m_window(nullptr);

GameEngine::GameEngine()
{
	//Empty
}

GameEngine::~GameEngine()
{
	onEnd();
}

GameEngine* GameEngine::getInstance()
{
	//Check to see if it has already been initialized
	if (m_gameEngineInstance == nullptr) {
		m_gameEngineInstance = new GameEngine();
	}
	return m_gameEngineInstance;
}

bool GameEngine::onStart()
{
	m_window = new Window();
	m_window->initialize("Demo", 800, 600, 0);

	m_camera = new Camera();
	m_inputManager = new InputManager();
	m_sceneGraph = new SceneGraph();

	//Check if the game interface exists
	if (gameInterface != nullptr) {
		if (gameInterface->onStart() == false) {
			return false;
		}
	}
	else {
		return false;
	}

	return true;
}

void GameEngine::onEnd()
{
	exit(0);

	m_window->shutdown();
	m_window = nullptr;

	SDL_Quit();
}

void GameEngine::run()
{
	//Set the isRunning state to true the first time this method is called
	m_isRunning = true;

	//Maintain the game loop while this engine is running
	while (m_isRunning) {
		processInput();
		update();
		preRender();
		render();
		postRender();
		logMessage();
	}
}

void GameEngine::processInput()
{
	//Update the InputManager
	m_inputManager->update();

	SDL_Event evnt;

	//We toss in the event as a reference so that SDL_PollEvent will modifiy it internally and
	//then leave it for us to look at.
	while (SDL_PollEvent(&evnt)) {

		if (evnt.type == SDL_QUIT)
			m_isRunning = false;

		if (evnt.type == SDL_KEYDOWN)
			m_inputManager->pressKey(evnt.key.keysym.sym);

		if (evnt.type == SDL_KEYUP)
			m_inputManager->releaseKey(evnt.key.keysym.sym);

		if (evnt.type == SDL_MOUSEBUTTONDOWN)
			m_inputManager->pressKey(evnt.key.keysym.sym);

		if (evnt.type == SDL_MOUSEBUTTONUP)
			m_inputManager->releaseKey(evnt.key.keysym.sym);

		if (evnt.type == SDL_MOUSEMOTION)
			m_inputManager->setMouseCoords(evnt.motion.x, evnt.motion.y);
	}

	gameInterface->processInput();
}

void GameEngine::update()
{
	gameInterface->update();
}

void GameEngine::preRender()
{
	gameInterface->preRender();
}

void GameEngine::render()
{
	gameInterface->render();
}

void GameEngine::postRender()
{
	gameInterface->postRender();
}

void GameEngine::logMessage()
{
	gameInterface->logMessage();
}