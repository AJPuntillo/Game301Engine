#include "OpenGLRenderer.h"

using namespace ENGINE;


OpenGLRenderer::OpenGLRenderer()
{
	manager = new ResourceManager<Mesh>;
	manager->put(std::string("triangle"), triangleMesh);
	manager->get("triangle");
	ResourceHandle<Mesh> test = manager->get("triangle");
	triangleShader = new Shader("D:/Year 3 - Semester 5/Game 301 - Game Engine Design/Game301Engine/Game301Engine/Shaders/Shader_Vert.vs", "D:/Year 3 - Semester 5/Game 301 - Game Engine Design/Game301Engine/Game301Engine/Shaders/Shader_Frag.vs");
	triangleMesh = new Mesh();
	test.getIndex();
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
	triangleMesh->render();
}