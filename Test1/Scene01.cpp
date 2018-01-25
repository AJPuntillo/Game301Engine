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
	shader = new Shader("../Game301Engine/Shaders/primitiveCubeVert.glsl", "../Game301Engine/Shaders/primitiveCubeFrag.glsl");
	shader_colour = new Shader("../Game301Engine/Shaders/ColourShaderVert.vs", "../Game301Engine/Shaders/ColourShaderFrag.vs");

	//Models
	model = new Model();

	//Shader Manager
	shaderHandle = ShaderManager::getInstance()->storeShader(shader, std::string("shader1"));
	shader_colour_Handle = ShaderManager::getInstance()->storeShader(shader_colour, std::string("shader2"));

	//Model Manager
	modelHandle = ModelManager::getInstance()->storeModel(model, std::string("model1"));

	//Image Manager
	crateImage = ImageManager::getInstance()->loadFile(std::string("Crate"), std::string("Resources/crate.jpg"));
	crate2Image = ImageManager::getInstance()->loadFile(std::string("Crate2"), std::string("Resources/crate2.png"));

	//Material Manager
	crateMaterialHandle = MaterialManager::getInstance()->addMaterial(std::string("CrateMaterial1"));
	MaterialManager::getInstance()->getMaterial(crateMaterialHandle)->addTextureMap(Material::TextureType::MAT_DIFFUSE, crateImage);
	//crate2MaterialHandle = MaterialManager::getInstance()->addMaterial(std::string("CrateMaterial2"));
	//MaterialManager::getInstance()->getMaterial(crateMaterialHandle)->addTextureMap(Material::TextureType::MAT_DIFFUSE, crate2Image);
	
	//GameObjects
	obj1 = new GameObject(modelHandle, shaderHandle, crateMaterialHandle);
	obj2 = new GameObject(modelHandle, shaderHandle, crateMaterialHandle);

	//Push new matrix onto the stack (Copies the previous matrix)
	mStack.pushModelView();
	//Make transformation changes
	mStack.translateBy(-1.0f, 0.0f, 0.0f);
	obj1->m_boundingVolume->movedBy(glm::vec3(-1.0f, 0.0f, 0.0f));
	//mStack.rotateBy(90.0f, 1.0f, 1.0f, 0.0f);
	//mStack.scaleBy(0.5f, 0.5f, 0.5f);
	//Set the node's matrix to the current model matrix on the stack
	obj1->m_sceneNode->m_modelMatrix = mStack.getModelMatrix();
	
	mStack.popModelView(); //Pop if you want the matrix to be affected by the previous matrix on the stack (In this case, it will be the first matrix AKA the identity matrix)
	mStack.pushModelView();
	mStack.translateBy(1.0f, 0.0f, 0.0f);
	obj2->m_boundingVolume->movedBy(glm::vec3(1.0f, 0.0f, 0.0f));
	//mStack.rotateBy(45.0f, 1.0f, 0.0f, 1.0f);
	mStack.scaleBy(0.5f, 0.5f, 0.5f);
	obj2->m_sceneNode->m_modelMatrix = mStack.getModelMatrix();

	return true;
}

void Scene01::onEnd()
{

}

void Scene01::processInput()
{
	float currentFrame = (SDL_GetTicks() / 1000);
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	Camera* m_camera = GameEngine::getInstance()->getCamera();
	InputManager* m_inputManager = GameEngine::getInstance()->getInputManager();

	//Camera movement with mouse
	m_camera->processMouse(m_inputManager);

	//Camera movement with keys--
	if (m_inputManager->isKeyDown(SDLK_w))
		m_camera->processKeyboard(FORWARD, deltaTime);

	if (m_inputManager->isKeyDown(SDLK_s))
		m_camera->processKeyboard(BACKWARD, deltaTime);

	if (m_inputManager->isKeyDown(SDLK_a))
		m_camera->processKeyboard(LEFT, deltaTime);

	if (m_inputManager->isKeyDown(SDLK_d))
		m_camera->processKeyboard(RIGHT, deltaTime);
	//--

	if (m_inputManager->isKeyDown(SDLK_g)) {
		mStack.translateBy(0.003f, 0.0f, 0.0f);
		obj2->m_boundingVolume->movedBy(glm::vec3(0.003f, 0.0f, 0.0f));
		obj2->m_sceneNode->m_modelMatrix = mStack.getModelMatrix();
	}

	if (m_inputManager->isKeyDown(SDLK_f)) {
		mStack.translateBy(-0.003f, 0.0f, 0.0f);
		obj2->m_boundingVolume->movedBy(glm::vec3(-0.003f, 0.0f, 0.0f));
		obj2->m_sceneNode->m_modelMatrix = mStack.getModelMatrix();
	}
}

void Scene01::update()
{
	if (obj1->m_boundingVolume->isColliding(*obj2->m_boundingVolume)) {
		std::cout << "COLLISION DETECTED" << std::endl;
	}
}

void Scene01::preRender()
{
	//Clear renderer
	renderer->clearBuffers(/*glm::vec4(0.0f, 0.0f, 0.5f, 1.0f)*/);
}

void Scene01::render()
{
	//Render
	SceneNode* sn = GameEngine::getInstance()->getSceneGraph()->getRootSceneNode();
	renderer->renderSceneNode(sn);
}

void Scene01::postRender()
{
	//Swap buffers
	renderer->swapBuffers(GameEngine::getInstance()->getWindow());
}

void Scene01::logMessage()
{

}