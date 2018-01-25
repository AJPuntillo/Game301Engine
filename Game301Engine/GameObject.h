#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameEngine.h"
#include "Entity.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "MaterialManager.h"
#include "SceneNode.h"
#include "BoundingVolume.h"

namespace ENGINE {

	class GameObject : public Entity
	{
	public:
		GameObject();
		GameObject(Model* model_, ResourceHandle<Shader> shaderName_, ResourceHandle<Material> materialName_ = -1);
		GameObject(ModelManager::HandleType modelHandle_, ResourceHandle<Shader> shaderName_, ResourceHandle<Material> materialName_ = -1);
		~GameObject();

		void render() override;

		void attachModel(Model* model);
		void detachModel();

		//Getters
		Model* getAttachedModel() const { return m_model; }
		Shader* getAttachedShader() const;
		glm::mat4 getModelMatrix() { return m_sceneNode->getModelMatrix(); }
		BoundingVolume* getBoundingVolume() { return m_boundingVolume; }

		SceneNode* m_sceneNode;
		BoundingVolume* m_boundingVolume;

	private:
		Model* m_model;
		ResourceHandle<Model> mHandle;
		ResourceHandle<Shader> m_shaderName;
		ResourceHandle<Material> m_materialName;
	};

}

#endif