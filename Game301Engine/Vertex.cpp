#include "Vertex.h"

using namespace ENGINE;

//VERTEX COMPONENT DESCRIPTOR CLASS

VertexComponentDescriptor::VertexComponentDescriptor() :
	type(VertexComponentType::VC_NONE),
	offset(0)
{
	//Empty
}

int VertexComponentDescriptor::getSize()
{
	int result = 0;

	switch (type)
	{
	case VC_TEXCOORDS_2F:
		result = 2;// *sizeof(float);
		break;
	case VC_POSITION_3F:
	case VC_COLOUR_3F:
	case VC_NORMALS_3F:
		result = 3;// *sizeof(float);
		break;
	case VC_COLOUR_4F:
		result = 4;// *sizeof(float);
		break;
	}

	return result;
}

int VertexComponentDescriptor::getNumFloats()
{
	int result = 0;

	switch (type)
	{
	case VC_TEXCOORDS_2F:
		result = 2;
		break;
	case VC_POSITION_3F:
	case VC_COLOUR_3F:
	case VC_NORMALS_3F:
		result = 3;
		break;
	case VC_COLOUR_4F:
		result = 4;
		break;
	}

	return result;
}

//VERTEX DESCRIPTOR CLASS

VertexDescriptor::VertexDescriptor()
{
	//Empty
}

void VertexDescriptor::addComponent(VertexComponentDescriptor::VertexComponentType type)
{
	VertexComponentDescriptor tmp;

	tmp.type = type;
	tmp.offset = stride;
	stride += tmp.getSize();
	componentList.push_back(tmp);
}

int VertexDescriptor::getStride()
{
	return stride;
}

int VertexDescriptor::getSize()
{
	return componentList.size();
}