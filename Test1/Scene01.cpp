#include "Scene01.h"

using namespace ENGINE;

Scene01::Scene01()
{
}

Scene01::~Scene01()
{
}

bool Scene01::onStart()
{
	triangle = new OpenGLRenderer();
	return true;
}

void Scene01::onEnd()
{

}

void Scene01::update()
{

}

void Scene01::preRender()
{

}

void Scene01::render()
{
	//Rendering
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	triangle->renderPrimitive();

	//Swap buffers
	GameEngine::getInstance()->getWindow()->swapBuffers();
}

void Scene01::postRender()
{

}

void Scene01::logMessage()
{

}