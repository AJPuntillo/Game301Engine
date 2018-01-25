#include "OpenGLRenderer.h"

using namespace ENGINE;

OpenGLRenderer::OpenGLRenderer()
{

}

OpenGLRenderer::~OpenGLRenderer()
{
	//Empty
}

void OpenGLRenderer::render(GameObject* obj_) {

	//Initialize/update View and Projection matrices
	Camera* cam = GameEngine::getInstance()->getCamera();
	cam->createViewMatrix();
	cam->createProjectionMatrix(GameEngine::getInstance()->getWindow()->getScreenWidth(), GameEngine::getInstance()->getWindow()->getScreenHeight());

	obj_->getAttachedShader()->setMat4("projection", cam->getProj());
	obj_->getAttachedShader()->setMat4("view", cam->getView());

	BoundingVolume* mdlBox = obj_->m_boundingVolume;
	bool zeroBox = mdlBox->getMaxCorner() == mdlBox->getMinCorner();
	bool shouldRender = zeroBox || (!(Frustrum::Frustrum::EnclosureType::OUTSIDE == cam->getFrustrum()->isInside(mdlBox)));
	if (!shouldRender)
	{
		std::cout << "MODEL IS CULLED" << std::endl;
	}
	else
	{
		obj_->render();
	}
}

void OpenGLRenderer::renderSceneGraph(SceneNode* rootNode_) {

	SceneNode::model_iterator iter = rootNode_->modelBegin();
	while (iter != rootNode_->modelEnd())
	{
		GameObject* model = *iter;
		render(model);
		iter++;
	}

	SceneNode* child = rootNode_->getFirstChild();
	while (child != NULL)
	{
		renderSceneNode(child);
		child = child->getNextSibling();
	}
}

void OpenGLRenderer::renderSceneNode(SceneNode* sceneNode_)
{
	SceneNode::model_iterator iter = sceneNode_->modelBegin();
	while (iter != sceneNode_->modelEnd())
	{
		GameObject* model = *iter;
		render(model);

		iter++;
	}

	SceneNode* child = sceneNode_->getFirstChild();
	while (child != NULL)
	{
		renderSceneNode(child);
		child = child->getNextSibling();
	}
}

void OpenGLRenderer::clearBuffers(glm::vec4 clearColour_)
{
	glClearColor(clearColour_.x, clearColour_.y, clearColour_.z, clearColour_.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::swapBuffers(Window* window_)
{
	window_->swapBuffers();
}