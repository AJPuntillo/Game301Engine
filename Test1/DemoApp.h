#pragma once
#ifndef DEMOAPP_H
#define DEMOAPP_H

#include <Game301Engine/GameEngine.h>
#include <Game301Engine/GameInterface.h>
#include <Game301Engine/SceneInterface.h>

class DemoApp : public ENGINE::GameInterface
{
public:
	DemoApp();
	virtual ~DemoApp();

	virtual bool onStart() override;
	virtual void onEnd() override;
	virtual void processInput() override;
	virtual void update() override;
	virtual void preRender() override;
	virtual void render() override;
	virtual void postRender() override;
	virtual void logMessage() override;


private:
	int m_currentSceneIndex = 0;
	ENGINE::SceneInterface* m_currentScene = nullptr;
};

#endif