#include <opengl/opengl.h>
#include <myriad/myrRenderer.h>

#include <iostream>

myr::Renderer::Renderer(const Color clearColor, const Rect size)
	:renderTarget(clearColor, size)
{
	ogl_LoadFunctions();

	renderTarget.setRect(size);
}

myr::Renderer::~Renderer()
{
	
}

myr::DefaultRenderTarget &myr::Renderer::getRenderTarget()
{
	return renderTarget;
}

void myr::Renderer::render()
{
	renderTarget.unbind();
}
