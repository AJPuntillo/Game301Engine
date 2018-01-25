#include "MaterialManager.h"

using namespace ENGINE;

MaterialManager* MaterialManager::m_instance = nullptr;

MaterialManager::MaterialManager()
{
	//Empty
}

MaterialManager::~MaterialManager()
{
	m_MaterialeResources.clearKeysAndValues();
}


MaterialManager* MaterialManager::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new MaterialManager();
	}
	return m_instance;
}

MaterialManager::HandleType MaterialManager::addMaterial(const std::string &name_)
{
	MaterialManager::HandleType result;

	Material* mat = new Material();
	result = storeMaterial(mat, name_);

	return result;
}

MaterialManager::HandleType MaterialManager::storeMaterial(const Material* material_, const std::string &name_)
{
	MaterialManager::HandleType	result(-1);

	//Is name already in use?
	result = m_MaterialeResources.get(name_);
	if (!result.isNull()) {
		throw std::string("Name in use");
	}

	result = m_MaterialeResources.put((std::string&)name_, (Material*)material_);
	return result;
}

void MaterialManager::deleteMaterial(const std::string &name_)
{
	HandleType result = m_MaterialeResources.get(name_);
	if (!result.isNull()) {
		throw std::string("Material not found");
	}
	m_MaterialeResources.remove((std::string&)name_);
}

MaterialManager::HandleType MaterialManager::getMaterial(const std::string &name_)
{
	MaterialManager::HandleType	result(-1);
	result = m_MaterialeResources.get(name_);

	return result;
}

Material* MaterialManager::getMaterial(const MaterialManager::HandleType &handle_)
{
	Material *result = m_MaterialeResources.get((MaterialManager::HandleType)handle_);

	return result;
}
