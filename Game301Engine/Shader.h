#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace ENGINE {

	class Shader {
	public:
		//The constructor reads and builds the shader
		Shader(const std::string vertexPath, const std::string fragmentPath);
		~Shader();

		//Use/Activate the shader
		void use();
		//Getters
		GLuint getShaderProgram() { return m_programId; }
		//Utility uniform functions
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
		void setVec3(const std::string &name, const glm::vec3 &value) const;
		void setVec4(const std::string &name, const glm::vec4 &value) const;
		void setMat4(const std::string &name, const glm::mat4 &mat) const;

	private:
		//Utility function for checking shader compilation/linking errors.
		void checkCompileErrors(GLuint shader, std::string type);

		//Program ID
		GLuint m_programId;
	};

}

#endif