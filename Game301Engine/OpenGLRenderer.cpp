#include "OpenGLRenderer.h"

using namespace ENGINE;


OpenGLRenderer::OpenGLRenderer()
{
	triangleShader = new Shader("D:/Year 3 - Semester 5/Game 301 - Game Engine Design/Game301Engine/Game301Engine/Shaders/Shader_Vert.vs", "D:/Year 3 - Semester 5/Game 301 - Game Engine Design/Game301Engine/Game301Engine/Shaders/Shader_Frag.vs");
	triangleMesh = new Mesh();

	manager = new ResourceManager<Mesh>;
	handle = manager->put(std::string("triangle"), triangleMesh);
}

OpenGLRenderer::~OpenGLRenderer()
{
	delete triangleMesh;
	delete triangleShader;
	delete vertexDescriptor;
}

void OpenGLRenderer::renderPrimitive()
{
	triangleShader->use();
	manager->get(handle)->render();
}