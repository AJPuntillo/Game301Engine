#pragma once
#ifndef EFFECTEDMODEL_H
#define EFFECTEDMODEL_H

#include "Model.h"
#include "ModelManager.h"

namespace ENGINE {

	class EffectedModel : public Entity
	{
	public:
		EffectedModel(ModelManager::HandleType model_);
		virtual ~EffectedModel();

		void rotate(const float angle_, const glm::vec3& vec_);
		void translate(const glm::vec3& vec_);
		void scale(const glm::vec3& vec_);

		void render(Shader* shader_);
		void render(Shader* shader_, MaterialManager::HandleType material_); //Overload with a Material

		//Getter
		ResourceHandle<Model>getModelHandle() { return m_modelHandle; }

	private:
		ResourceHandle<Model> m_modelHandle;
		Model* m_model;
	};

}

#endif