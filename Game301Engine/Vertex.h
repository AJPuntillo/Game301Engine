//Andrew Puntillo
//---
//Vertex Class:
//Contains an enum of float types that can potentially populate a model's vertex struct.
//Whenever the addComponent method is called, the vertex increases stride and offset to be used for dynamically populate vertex attributes.
//---

/*CURRENT QUESTIONS: How do I send vertex data to the struct? How do I keep the stride of the vertex in proper order? */

#pragma once
#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>

namespace ENGINE {

	class VertexComponentDescriptor
	{
	public:
		enum VertexComponentType{
			VC_NONE = 0,
			VC_POSITION_3F,
			VC_NORMALS_3F,
			VC_TEXCOORDS_2F,
			VC_COLOUR_3F,
			VC_COLOUR_4F
		};

		VertexComponentDescriptor();

		int getSize(); 			//Get the size (in bytes) of the component type
		int getNumFloats();		//Get the number of floats of the component type

		int offset;
		VertexComponentType type;
	};

	class VertexDescriptor
	{
	public:
		VertexDescriptor();

		void addComponent(VertexComponentDescriptor::VertexComponentType type);

		//Getters
		int getStride();	//Get stride
		int getSize();	//Get size of the Vertex (returns size of componentList)

		std::vector<VertexComponentDescriptor> componentList;
		int stride = 0;
	};

}

#endif