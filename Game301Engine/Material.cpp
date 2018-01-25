#include "Material.h"

using namespace ENGINE;

Material::Material()
{
}


Material::~Material()
{
}

void Material::bindTextures(Shader* shader_)
{
	shader_->use();
	if (m_textureDiffuse) {
		shader_->setInt("texture_diffuse1", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_textureDiffuse);
	}

	if (m_textureSpecular) {
		shader_->setInt("texture_specular1", 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_textureSpecular);
	}
}

void Material::addTextureMap(TextureType textureType_, ImageManager::HandleType imageHandle_)
{
	switch (textureType_) {
		case TextureType::MAT_DIFFUSE:
			m_textureDiffuse = loadTexture(imageHandle_);
			break;

		case TextureType::MAT_SPECULAR:
			m_textureSpecular = loadTexture(imageHandle_);
			break;

		default:
			std::cout << "ERROR::Unknown texture type" << std::endl;
			break;
	}
}

unsigned int Material::loadTexture(ImageManager::HandleType imageHandle_)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	if (ImageManager::getInstance()->getImage(imageHandle_)->getImage())
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, ImageManager::getInstance()->getImage(imageHandle_)->getFormat(),
			ImageManager::getInstance()->getImage(imageHandle_)->getWidth(),
			ImageManager::getInstance()->getImage(imageHandle_)->getHeight(),
			0,
			ImageManager::getInstance()->getImage(imageHandle_)->getFormat(),
			GL_UNSIGNED_BYTE,
			ImageManager::getInstance()->getImage(imageHandle_)->getImage());
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ImageManager::getInstance()->getImage(imageHandle_)->getFormat() == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); //Depending on the format, choose repeat or clamp to edge
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ImageManager::getInstance()->getImage(imageHandle_)->getFormat() == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//stbi_set_flip_vertically_on_load(true); //Flippy

		stbi_image_free(ImageManager::getInstance()->getImage(imageHandle_)->getImage());
	}
	else
	{
		std::cout << "Texture failed to load" << std::endl;
		stbi_image_free(ImageManager::getInstance()->getImage(imageHandle_)->getImage());
	}
	glBindTexture(GL_TEXTURE_2D, 0); //As a precaution, unbind the texture after it has been created
	return textureID;
}