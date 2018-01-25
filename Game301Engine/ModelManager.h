//Andrew Puntillo
//---
//Model Manager Class:
//The model manager stores models to a hashtable using strings and handles.
//It is a singleton class so that it can be accessed anywhere in the engine and that there will only be one.
//---

#pragma once
#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "ResourceManager.h"
#include "Model.h"

namespace ENGINE {

	class ModelManager
	{
	public:
		ModelManager();
		~ModelManager();

		typedef ResourceHandle<Model> HandleType;

		ModelManager::HandleType addModel(const std::string &name_);
		ModelManager::HandleType storeModel(const Model* model_, const std::string &name_);
		void deleteModel(const std::string &name_);

		//Getters
		static ModelManager* getInstance();
		Model* getModel(ModelManager::HandleType& handle_);
		Model* getModel(std::string& name_);

	private:
		ResourceManager<Model> m_modelResources;
		static ModelManager* m_instance;
	};

}

#endif