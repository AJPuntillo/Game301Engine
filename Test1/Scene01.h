#pragma once
#ifndef SCENE01_H
#define SCENE01_H

#include <Game301Engine/SceneInterface.h>
#include <Game301Engine/ResourceManager.h>
#include <Game301Engine/OpenGLRenderer.h>
#include <Game301Engine/Mesh.h>

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
	//Renderer
	ENGINE::OpenGLRenderer* renderer;

	//Shaders
	ENGINE::Shader* triangleShader;

	//Meshes
	ENGINE::Mesh* triangleMesh;

	//Resource Handles
	ENGINE::ResourceHandle<ENGINE::Mesh> triangleHandle;
	ENGINE::ResourceHandle<ENGINE::Shader> shaderHandle;
};

#endif