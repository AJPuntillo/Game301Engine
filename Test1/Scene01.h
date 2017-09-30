#pragma once
#ifndef SCENE01_H
#define SCENE01_H

#include <Game301Engine/SceneInterface.h>
#include <Game301Engine/OpenGLRenderer.h>

class Scene01 : public ENGINE::SceneInterface
{
public:
	Scene01();
	virtual ~Scene01();

	virtual bool onStart();
	virtual void onEnd();
	virtual void update();
	virtual void preRender();
	virtual void render();
	virtual void postRender();
	virtual void logMessage();

private:
	ENGINE::OpenGLRenderer* triangle;
};

#endif