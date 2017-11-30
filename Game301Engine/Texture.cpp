#include "Texture.h"

#include <iostream>

using namespace ENGINE;
Texture::Texture(std::string& path_)
{
	imageData = stbi_load(path_.c_str(), &m_width, &m_height, &m_format, 0);

	if (!imageData)
		std::cout << "ERROR::Image could not be loaded!" << std::endl;
}

Texture::~Texture()
{
	//Empty
}
