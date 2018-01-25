//Andrew Puntillo
//---
//Material Class:
//The material covers the model. This class contains values that alter how the model is displayed.
//Alterations include the texture, the diffuse, the ambient, and the specular.
//---

#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

#include "ImageManager.h"
#include "Shader.h"

namespace ENGINE {

	class Material
	{
	public:

		enum TextureType {
			MAT_DIFFUSE,
			MAT_SPECULAR
		};


		Material();
		~Material();

		void bindTextures(Shader* shader_);

		void addTextureMap(TextureType textureType_, ImageManager::HandleType imageHandle_);
		unsigned int loadTexture(ImageManager::HandleType imageHandle_);

		//Getters
		glm::vec3 getAmbient()		{ return m_ambient; }
		glm::vec3 getDiffuse()		{ return m_diffuse; }
		glm::vec3 getSpecular()		{ return m_specular; }
		float getShininess()		{ return m_shininess; }

		//Setters
		void setAmbient(glm::vec3 ambient_)		{ m_ambient = ambient_; }
		void setDiffuse(glm::vec3 diffuse_)		{ m_diffuse = diffuse_; }
		void setSpecular(glm::vec3 specular_)	{ m_specular = specular_; }
		void setShininess(float shininess_)		{ m_shininess = shininess_; }

	private:
		//Texture maps					//Defaults
		unsigned int m_textureDiffuse	= 0;
		unsigned int m_textureSpecular	= 0;

		//Colour intensity				
		glm::vec3 m_ambient				= glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_diffuse				= glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_specular			= glm::vec3(0.0f, 0.0f, 0.0f);
		float m_shininess				= 64.0f;
	};

}

#endif