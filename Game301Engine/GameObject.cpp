#include "GameObject.h"

using namespace ENGINE;

GameObject::GameObject()
{
	m_sceneNode = nullptr;
	m_model = nullptr;
	m_boundingVolume = new BoundingVolume();
}

GameObject::GameObject(Model* model_, ResourceHandle<Shader> shaderName_, ResourceHandle<Material> materialName_)
{
	m_sceneNode = new SceneNode();
	m_sceneNode->addModel(this);
	GameEngine::getInstance()->getSceneGraph()->getRootSceneNode()->appendChild(m_sceneNode);
	m_boundingVolume = new BoundingVolume();
	attachModel(model_);

	m_shaderName = shaderName_;
	m_materialName = materialName_;
}

GameObject::GameObject(ModelManager::HandleType modelHandle_, ResourceHandle<Shader> shaderName_, ResourceHandle<Material> materialName_)
{
	m_sceneNode = new SceneNode();
	m_sceneNode->addModel(this);
	GameEngine::getInstance()->getSceneGraph()->getRootSceneNode()->appendChild(m_sceneNode);
	m_boundingVolume = new BoundingVolume();
	Model* modelPtr;
	modelPtr = ModelManager::getInstance()->getModel(modelHandle_);
	attachModel(modelPtr);
	mHandle = modelHandle_;

	m_shaderName = shaderName_;
	m_materialName = materialName_;
}

GameObject::~GameObject()
{
	//Empty
}

void GameObject::render()
{
	//Retrieve the shader
	Shader* tempShader = ShaderManager::getInstance()->getShader(m_shaderName); //STOP THE BLEEDING

	//Bind the shader
	tempShader->use();

	//Set the Model matrix	
	glm::mat4 model = m_sceneNode->getModelMatrix();
	tempShader->setMat4("model", model);

	if (!m_materialName.isNull()) {
		//Retrieve the material
		Material* tempMat = MaterialManager::getInstance()->getMaterial(m_materialName);

		//Bind the textures
		tempMat->bindTextures(tempShader);
	}

	m_model->render();
	//ModelManager::getInstance()->getModel(mHandle)->render(); //USING POINTER TO ORIGINAL MODEL IN MANAGER... SHOULD I?

	//Unbind the texture as a precaution
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GameObject::attachModel(Model* model)
{
	m_model = model;
	m_boundingVolume->setupVolume(*m_model);
}

void GameObject::detachModel()
{
	m_model = nullptr;
}

Shader* GameObject::getAttachedShader() const {
	Shader* temp = ShaderManager::getInstance()->getShader(m_shaderName);
	return temp;
}