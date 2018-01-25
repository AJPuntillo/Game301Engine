//Andrew Puntillo
//---
//Abstract Renderer Class:
//An interface class that will be inherited to render specifc shapes/primitives.
//---

#pragma once
#ifndef ABSTRACTRENDERER_H
#define ABSTRACTRENDERER_H

#include <GL/glew.h>
#include "Shader.h"
#include "ResourceManager.h"

namespace ENGINE
{

	//Interface Class
	class AbstractRenderer
	{
	public:
		AbstractRenderer() {};
		virtual ~AbstractRenderer() {};
	};

}

#endif