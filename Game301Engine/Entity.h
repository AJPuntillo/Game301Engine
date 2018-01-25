//Andrew Puntillo
//---
//Entity Class:
//Abstract class that acts as the base of all GameObjects.
//---

#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>

#include "Shader.h"

namespace ENGINE {

	class Entity
	{
	public:

		Entity() {};
		virtual ~Entity() {};

		virtual void render() = 0;
	};

}

#endif