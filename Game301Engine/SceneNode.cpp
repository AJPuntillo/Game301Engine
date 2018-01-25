#include "SceneNode.h"

using namespace ENGINE;

SceneNode::SceneNode()
{
	m_firstChild = m_lastChild = m_prevSibling = m_nextSibling = m_parent = nullptr;
	m_orientation = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_location = glm::vec3(0.0f, 0.0f, 0.0f);
	m_userData = nullptr;
}

SceneNode::SceneNode(const glm::vec3 &loc, const glm::vec4 &orient, const glm::vec3 &scaling)  
{
	m_location = loc;
	m_orientation = orient;
	m_scale = scaling;
	m_firstChild = m_lastChild = m_prevSibling = m_nextSibling = m_parent = nullptr;
	m_userData = nullptr;
}

SceneNode::SceneNode(const SceneNode &other)
{
	m_location = other.m_location;
	m_orientation = other.m_orientation;
	m_scale = other.m_scale;
	m_firstChild = m_lastChild = m_prevSibling = m_nextSibling = m_parent = nullptr;
	m_userData = other.m_userData;
}

SceneNode::~SceneNode()
{
	if (m_userData)
	{
		delete m_userData;
		m_userData = nullptr;
	}
}

void SceneNode::appendChild(SceneNode* node)
{
	if (m_lastChild == nullptr)
	{
		m_firstChild = node;
	}
	else
	{
		m_lastChild->m_nextSibling = node;
		node->m_prevSibling = m_lastChild;
	}
	m_lastChild = node;
	node->m_parent = this;
}

void SceneNode::removeChild(SceneNode* node)
{
	SceneNode *curr;

	for (curr = m_firstChild; curr != nullptr; curr = curr->m_nextSibling)
	{
		if (curr == node)
		{
			if (node->m_prevSibling)
			{
				node->m_prevSibling->m_nextSibling = node->m_nextSibling;
			}
			else
			{
				m_firstChild = node->m_nextSibling;
			}
			if (node->m_nextSibling)
			{
				node->m_nextSibling->m_prevSibling = node->m_prevSibling;
			}
			else
			{
				m_lastChild = node->m_prevSibling;
			}
			node->m_parent = nullptr;
			return;
		}
	}

}

void SceneNode::addModel(GameObject* model)
{
	m_modelList.push_back(model);
}

void SceneNode::removeModel(GameObject* model)
{
	std::vector<GameObject*>::iterator iter = std::find(m_modelList.begin(), m_modelList.end(), model);
	if (iter != m_modelList.end())
	{
		m_modelList.erase(iter);
	}
}

SceneNode* SceneNode::getFirstChild() const {
	return m_firstChild;
}

SceneNode* SceneNode::getNextSibling() const {
	return m_nextSibling;
}

SceneNode::model_iterator SceneNode::modelBegin() {
	return m_modelList.begin();
}

SceneNode::model_iterator SceneNode::modelEnd() {
	return m_modelList.end();
}

int SceneNode::getNumberModels() const {
	return m_modelList.size();
}

glm::vec3 SceneNode::getLocation() const {
	glm::vec3 result = m_location;
	return result;
}

glm::vec3 SceneNode::getWorldLocation() const {
	glm::vec3 result = glm::vec3(0.0f, 0.0f, 0.0f);
	if (m_parent != nullptr)
	{
		result = m_parent->getWorldLocation();
	}
	result = result + m_location;
	return result;
}

glm::vec4 SceneNode::getOrientation() const {
	glm::vec4 result = m_orientation;
	return result;
}

void SceneNode::getRotateAbout(glm::vec3 &pt, glm::vec4 &rotation) {
	pt = m_rotateAboutPt;
	rotation = m_rotateAboutOrientation;
}

glm::vec3 SceneNode::getScaleFactor() const {
	glm::vec3 result = m_scale;
	return result;
}