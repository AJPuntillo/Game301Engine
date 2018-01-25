//#include "EffectedModel.h"
//
//using namespace ENGINE;
//
//EffectedModel::EffectedModel(ModelManager::HandleType model_)
//{
//	m_modelHandle = model_;
//	m_model = ModelManager::getInstance()->getModel(m_modelHandle);
//}
//
//EffectedModel::~EffectedModel()
//{
//
//}
//
//void EffectedModel::rotate(const float angle_, const glm::vec3& vec_)
//{
//	m_rotationMatrix = glm::rotate(m_rotationMatrix, angle_, vec_);
//}
//void EffectedModel::translate(const glm::vec3& vec_)
//{
//	m_translateMatrix = glm::translate(m_translateMatrix, vec_);
//	m_pos += vec_;
//}
//void EffectedModel::scale(const glm::vec3& vec_)
//{
//	m_scaleMatrix = glm::scale(m_scaleMatrix, vec_);
//}
//
//void EffectedModel::render(Shader* shader_)
//{
//	//Set the Model matrix	
//	m_modelMatrix = m_translateMatrix * m_rotationMatrix * m_scaleMatrix;
//	shader_->setMat4("model", m_modelMatrix);
//
//	//Render
//	m_model->render(shader_);
//
//	glBindTexture(GL_TEXTURE_2D, 0); //Unbind the texture as a precaution
//}
//
//void EffectedModel::render(Shader* shader_, MaterialManager::HandleType material_)
//{
//	//Set the Model matrix	
//	m_modelMatrix = m_translateMatrix * m_rotationMatrix * m_scaleMatrix;
//	shader_->setMat4("model", m_modelMatrix);
//
//	//Material
//	MaterialManager::getInstance()->getMaterial(material_)->bindTextures(shader_);
//
//	//Render
//	m_model->render(shader_);
//
//	glBindTexture(GL_TEXTURE_2D, 0); //Unbind the texture as a precaution
//}
