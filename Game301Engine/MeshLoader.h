#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <GL/glew.h> //Holds all OpenGL type declarations
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace ENGINE {

	struct VertexStruct {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
		glm::vec3 tangent;
		glm::vec3 bitangent;
	};

	struct TextureLoader {
		unsigned int id;
		std::string type;
		aiString path;
	};

	class MeshLoader
	{
	public:
		MeshLoader(std::vector<VertexStruct> vertices_, std::vector<unsigned int> indices_, std::vector<TextureLoader> textures_);
		//~Mesh(); //Commented out for now, apparently its already defined?

		//Render the mesh
		void render(Shader* shader_);

		//Mesh data
		std::vector<VertexStruct> vertices;
		std::vector<unsigned int> indices;
		std::vector<TextureLoader> textures;

		//Getters
		unsigned int getVAO() { return m_VAO; }

	private:
		//Render data
		unsigned int m_VAO, m_VBO, m_EBO;

		//Initializes all the buffer objects/arrays
		void generateBuffers();
	};

}

#endif