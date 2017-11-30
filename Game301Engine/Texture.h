#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Image.h"
#include "stb_image.h"

namespace ENGINE {

	class Texture
	{
	public:
		Texture(std::string& path_);
		~Texture();

		//Getters
		unsigned char* getImage() { return imageData; };
		int getWidth() { return m_width; };
		int getHeight() { return m_height; };
		int getFormat() { 
			if (m_format == 1)
				return GL_RED;
			else if (m_format == 3)
				return GL_RGB;
			else if (m_format == 4)
				return GL_RGBA;
		};
		std::string getName() const { return m_imageName; };

		//Setters
		void setName(std::string& name_) { m_imageName = name_; };

	private:
		std::string	m_imageName;
		unsigned char* imageData;
		int m_width = 0;
		int m_height = 0;
		int m_format = 0;
	};

}

#endif