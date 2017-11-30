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
	//Renderer
	renderer = new OpenGLRenderer();

	//Shaders
	triangleShader = new Shader("D:/Year 3 - Semester 5/Game 301 - Game Engine Design/Game301Engine/Game301Engine/Shaders/TextureShaderVert.vs", "D:/Year 3 - Semester 5/Game 301 - Game Engine Design/Game301Engine/Game301Engine/Shaders/TextureShaderFrag.vs");

	//Meshes
	triangleMesh = new Mesh();

	//Resource Handles
	triangleHandle = renderer->getMeshManager()->put(std::string("triangle"), triangleMesh);
	shaderHandle = renderer->getShaderManager()->put(std::string("shader1"), triangleShader);

	//Image Manager
	crateImage = ImageManager::getInstance()->loadFile(std::string("Crate"), std::string("Resources/crate.jpg"));

	//Load Image
	m_texture = triangleMesh->loadTexture(crateImage);

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

	//Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	//Render
	renderer->renderPrimitive(shaderHandle, triangleHandle);

	//Swap buffers
	GameEngine::getInstance()->getWindow()->swapBuffers();
}

void Scene01::postRender()
{

}

void Scene01::logMessage()
{

}