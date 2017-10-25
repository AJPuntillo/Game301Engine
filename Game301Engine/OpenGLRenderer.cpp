#include "OpenGLRenderer.h"

using namespace ENGINE;


OpenGLRenderer::OpenGLRenderer()
{
	meshManager = new ResourceManager<Mesh>();
	shaderManager = new ResourceManager<Shader>();
}

OpenGLRenderer::~OpenGLRenderer()
{

}

void OpenGLRenderer::renderPrimitive(ResourceHandle<Shader> shader, ResourceHandle<Mesh> mesh)
{
	shaderManager->get(shader)->use();
	meshManager->get(mesh)->render();
}