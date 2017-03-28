#include <opengl/opengl.h>
#include <myriad/myrRenderer.h>

#include <iostream>

myr::Renderer::Renderer(const Color clearColor, const Rect size)
	:renderTarget(clearColor, size)
{
	ogl_LoadFunctions();
}

myr::Renderer::~Renderer()
{
	
}

void myr::Renderer::render()
{
	renderTarget.unbind();
}
