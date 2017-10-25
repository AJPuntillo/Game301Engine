#include "Texture.h"

using namespace ENGINE;

Texture::Texture(std::string& path_)
{
	imageData = stbi_load(path_.c_str(), &m_width, &m_height, &m_format, 0);
}

Texture::~Texture()
{
	//Empty
}
