#include "ImageManager.h"

using namespace ENGINE;

ImageManager* ImageManager::m_instance = nullptr;

ImageManager::ImageManager()
{
	//Empty
}

ImageManager::~ImageManager()
{
	clear();
}

ImageManager* ImageManager::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new ImageManager();
	}
	return m_instance;
}

ImageManager::HandleType ImageManager::loadFile(std::string& resName_, std::string& fileName_)
{
	ImageManager::HandleType result;

	Texture* img = new Texture(fileName_);
	result = loadImage(resName_, img);

	return result;
}

ImageManager::HandleType ImageManager::loadImage(std::string& resName_, Texture* image)
{
	ImageManager::HandleType result;

	result = m_imageResources.get(resName_);
	if (!result.isNull()) {
		throw std::string("Name in use");
	}
	image->setName(resName_);
	result = m_imageResources.put(resName_, image);

	return result;
}

void ImageManager::releaseImage(std::string& name_)
{
	m_imageResources.remove(name_);
}

void ImageManager::deleteImage(std::string& name_)
{
	Texture *img = getImage(name_);
	m_imageResources.remove(name_);
	delete img;
}

void ImageManager::clear()
{
	m_imageResources.clearKeysAndValues();
}

Texture* ImageManager::getImage(ImageManager::HandleType& handle_)
{
	if (handle_.isNull()) throw std::string("NULL handle");

	Texture *result = m_imageResources.get(handle_);

	if (result == NULL)
	{
		throw std::string("Invalid handle");
	}

	return result;
}

Texture* ImageManager::getImage(std::string& name_)
{
	Texture* result = NULL;
	ImageManager::HandleType handle = m_imageResources.get(name_);

	if (handle.isNull())
	{
		throw std::string("Image name unknown");
	}

	result = getImage(handle);

	return result;
}

ImageManager::HandleType ImageManager::nameToHandle(const std::string& name_)
{
	return m_imageResources.get(name_);
}