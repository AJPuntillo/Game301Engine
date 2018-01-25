#pragma once
#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <glm/glm.hpp>

#include "SceneNode.h"
#include "AbstractRenderer.h"

namespace ENGINE {

	class SceneGraph
	{
	public:
		SceneGraph();
		~SceneGraph();

		void renderSceneGraph(AbstractRenderer &renderer_);

		//Getters
		SceneNode* getRootSceneNode() { return m_rootSceneNode; }


	private:
		void init();
		void renderSceneNode(SceneNode* sceneRoot, AbstractRenderer &renderer_);

		SceneNode* m_rootSceneNode;
		glm::vec3 m_renderOffset;
	};

}

#endif