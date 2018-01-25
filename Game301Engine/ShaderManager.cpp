#include "ShaderManager.h"

using namespace ENGINE;

ShaderManager* ShaderManager::m_instance = nullptr;

ShaderManager::ShaderManager()
{
	//Empty
}

ShaderManager::~ShaderManager()
{
	m_ShaderResources.clearKeysAndValues();
}


ShaderManager* ShaderManager::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new ShaderManager();
	}
	return m_instance;
}

ShaderManager::HandleType ShaderManager::addShader(const std::string &name_, const std::string &vertexPath_, std::string &fragmentPath_)
{
	ShaderManager::HandleType result;

	Shader* mat = new Shader(vertexPath_, fragmentPath_);
	result = storeShader(mat, name_);

	return result;
}

ShaderManager::HandleType ShaderManager::storeShader(const Shader* shader_, const std::string &name_)
{
	ShaderManager::HandleType	result(-1);

	//Is name already in use?
	result = m_ShaderResources.get(name_);
	if (!result.isNull()) {
		throw std::string("Name in use");
	}

	result = m_ShaderResources.put((std::string&)name_, (Shader*)shader_);
	return result;
}

void ShaderManager::deleteShader(const std::string &name_)
{
	HandleType result = m_ShaderResources.get(name_);
	if (!result.isNull()) {
		throw std::string("Shader not found");
	}
	m_ShaderResources.remove((std::string&)name_);
}

ShaderManager::HandleType ShaderManager::getShader(const std::string &name_)
{
	ShaderManager::HandleType	result(-1);
	result = m_ShaderResources.get(name_);

	return result;
}

Shader* ShaderManager::getShader(const ShaderManager::HandleType &handle_)
{
	Shader *result = m_ShaderResources.get((ShaderManager::HandleType)handle_);

	return result;
}
