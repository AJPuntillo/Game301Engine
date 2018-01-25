#include "SceneGraph.h"

using namespace ENGINE;

SceneGraph::SceneGraph()
{
	init();
}

SceneGraph::~SceneGraph()
{
	//Empty
}

void SceneGraph::init() {
	m_rootSceneNode = new SceneNode();
	m_rootSceneNode->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
}