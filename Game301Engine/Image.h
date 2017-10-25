#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <GL/glew.h>
#include <string>

namespace ENGINE {

	class Image
	{
	public:

		Image(int width, int height) {};
		Image(std::string& fname) {};
		~Image() {}

		//Getters
		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
		virtual int getBitsPerPixel() = 0;
		virtual GLenum getFormat() = 0;
		virtual GLenum getPixelType() = 0;
		virtual unsigned char* getImage() = 0;
		virtual GLenum getPixelStorageType() = 0;
		virtual int getPixelStorageParameter() = 0;
		std::string getName() const { return m_imageName; };

		//Setters
		virtual void setPixel(int x, int y, float r, float g, float b) = 0;
		void setName(std::string& nm) { m_imageName = nm; };


	protected:
		std::string	m_imageName;
		int m_width = 0;
		int m_height = 0;
		int m_format = 0;
	};
}

#endif