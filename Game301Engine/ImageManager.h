#pragma once
#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include "ResourceManager.h"
#include "Texture.h"

namespace ENGINE {

	class ImageManager
	{
	public:
		ImageManager();
		~ImageManager();

		typedef ResourceHandle<Texture>	HandleType;

		ImageManager::HandleType loadFile(std::string resName_, std::string path_);
		ImageManager::HandleType loadImage(std::string resName_, Texture* image);
		void releaseImage(std::string name_);
		void deleteImage(std::string name_);
		void clear();

		//Getters
		static ImageManager* getInstance();
		Texture* getImage(ImageManager::HandleType& handle_);
		Texture* getImage(std::string& name_);
		ImageManager::HandleType nameToHandle(const std::string& name_);

		private:
		ResourceManager<Texture> m_imageResources;
		static ImageManager* m_instance;

	};

}

#endif