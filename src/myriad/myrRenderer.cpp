#include <opengl/opengl.h>
#include <myriad/myrRenderer.h>

#include <iostream>

myr::Renderer::Renderer(const Color clearColor, const Rect rect)
	:renderTarget(clearColor, rect)
{
	ogl_LoadFunctions();
}

myr::Renderer::~Renderer()
{
	
}

void myr::Renderer::setRect(const Rect rect)
{
	renderTarget.setRect(rect);
}

myr::DefaultRenderTarget &myr::Renderer::getRenderTarget()
{
	return renderTarget;
}

void myr::Renderer::render()
{
	renderTarget.unbind();
}
