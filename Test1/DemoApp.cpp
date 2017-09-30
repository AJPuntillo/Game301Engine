#include "DemoApp.h"

#include "Scene01.h"

using namespace ENGINE;

DemoApp::DemoApp()
{
	//Empty
}

DemoApp::~DemoApp()
{
	delete m_currentScene;
	m_currentScene = nullptr;

	onEnd();
}

bool DemoApp::onStart()
{
	m_currentScene = new Scene01();

	m_currentScene->onStart();

	return true;
}

void DemoApp::onEnd()
{
	//Empty
}

void DemoApp::update()
{
	m_currentScene->update();
}

void DemoApp::preRender()
{
	m_currentScene->preRender();
}

void DemoApp::render()
{
	m_currentScene->render();
}

void DemoApp::postRender()
{
	m_currentScene->postRender();
}

void DemoApp::logMessage()
{
	m_currentScene->logMessage();
}