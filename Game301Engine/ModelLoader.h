#pragma once
#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

#include "Entity.h"
#include "MeshLoader.h"
#include "stb_image.h"
#include "ImageManager.h"
#include "MaterialManager.h"

#include <vector>

namespace ENGINE {

	class ModelLoader
	{
	public:
		//Expects a filepath to a 3D model.
		ModelLoader(std::string const& path_, bool gamma = false);
		~ModelLoader();

		//Updating and rendering
		void render(Shader* shader_);

		//Model Data
		std::vector<TextureLoader> textures_loaded; //Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
		std::vector<MeshLoader> meshes;
		std::string directory;
		bool gammaCorrection;

	private:
		//Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
		void loadModel(std::string const& path_);
		//Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
		void processNode(aiNode* node_, const aiScene* scene_);
		MeshLoader processMesh(aiMesh* mesh_, const aiScene* scene_);
		unsigned int loadTextureFromFile(const char* path_, const std::string& directory_, bool gamma = false);
		//Checks all material textures of a given type and loads the textures if they're not loaded yet
		//The required info is returned as a Texture struct
		std::vector<TextureLoader> loadMaterialTextures(aiMaterial* mat_, aiTextureType type_, std::string typeName_);
	};

}

#endif