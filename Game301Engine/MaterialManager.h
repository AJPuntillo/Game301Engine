#pragma once
#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include "ResourceManager.h"
#include "Material.h"

namespace ENGINE {

	class MaterialManager
	{
	public:
		MaterialManager();
		~MaterialManager();

		typedef ResourceHandle<Material> HandleType;

		MaterialManager::HandleType addMaterial(const std::string &name_);
		MaterialManager::HandleType storeMaterial(const Material* material_, const std::string &name_);
		void deleteMaterial(const std::string &name_);

		//Getters
		static MaterialManager* getInstance();
		MaterialManager::HandleType getMaterial(const std::string &name_);
		Material* getMaterial(const MaterialManager::HandleType &handle_);

	private:
		ResourceManager<Material> m_MaterialeResources;
		static MaterialManager* m_instance;
	};

}

#endif