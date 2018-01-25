#include "Model.h"

using namespace ENGINE;

Model::Model()
{
	loadMesh();
}

Model::~Model()
{

}

void Model::render()
{
	//Render
	m_mesh->render();
}

bool Model::loadMesh()
{
	m_mesh = new Mesh();
	return true;
}