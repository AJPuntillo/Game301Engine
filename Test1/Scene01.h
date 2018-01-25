#pragma once
#ifndef SCENE01_H
#define SCENE01_H

#include <Game301Engine/SceneInterface.h>
#include <Game301Engine/ResourceManager.h>
#include <Game301Engine/OpenGLRenderer.h>
#include <Game301Engine/Model.h>
#include <Game301Engine/EffectedModel.h>
#include <Game301Engine/GameEngine.h>
#include <Game301Engine/ShaderManager.h>
#include <Game301Engine/ModelManager.h>
#include <Game301Engine/ImageManager.h>
#include <Game301Engine/MaterialManager.h>
#include <Game301Engine/ModelLoader.h>

class Scene01 : public ENGINE::SceneInterface
{
public:
	Scene01();
	virtual ~Scene01();

	virtual bool onStart();
	virtual void onEnd();
	virtual void processInput();
	virtual void update();
	virtual void preRender();
	virtual void render();
	virtual void postRender();
	virtual void logMessage();

private:
	//Renderer
	ENGINE::OpenGLRenderer* renderer;

	//Shaders
	ENGINE::Shader* shader;
	ENGINE::Shader* shader_colour;

	//Models
	ENGINE::Model* model;

	//Resource Handles
	ENGINE::ResourceHandle<ENGINE::Model> modelHandle;
	ENGINE::ResourceHandle<ENGINE::Shader> shaderHandle;
	ENGINE::ResourceHandle<ENGINE::Shader> shader_colour_Handle;

	//Image Manager Handles
	ENGINE::ImageManager::HandleType crateImage;
	ENGINE::ImageManager::HandleType crate2Image;

	//Materials
	ENGINE::Material* crateMaterial;
	ENGINE::Material* crate2MAterial;

	//Material Handles
	ENGINE::MaterialManager::HandleType crateMaterialHandle;
	ENGINE::MaterialManager::HandleType crate2MaterialHandle;

	//Texture Data
	unsigned int m_texture;

	//GameObjects
	ENGINE::GameObject* obj1;
	ENGINE::GameObject* obj2;

	//Matrix Stack
	ENGINE::MatrixStack mStack; //Pushes an identity matrix when created

	//Makeshift Timestep
	float deltaTime = 0;
	float lastFrame = 0;
};

#endif