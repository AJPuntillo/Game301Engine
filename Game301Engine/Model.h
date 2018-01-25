//Andrew Puntillo
//---
//Model Class:
//The model class loads in a mesh and possibly a texture to be displayed in the renderer.
//Inherits from Entity.
//---

#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "Entity.h"
#include "Mesh.h"
#include "stb_image.h"
#include "ImageManager.h"
#include "MaterialManager.h"

#include <vector>

namespace ENGINE {

	class Model
	{
	public:
		Model();
		virtual ~Model();

		void render();

		bool loadMesh();

		//Getters
		Mesh* getMesh() { return m_mesh; }

	private:
		Mesh* m_mesh;
	};

}

#endif