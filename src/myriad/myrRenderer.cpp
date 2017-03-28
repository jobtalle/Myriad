#include <opengl/opengl.h>
#include <myriad/myrRenderer.h>

#include <iostream>

namespace {
	static bool initializedGL;
}

myr::Renderer::Renderer(const Color clearColor, const Rect rect)
	:renderTarget(clearColor, rect)
{
	if(!initializedGL)
	{
		ogl_LoadFunctions();
		initializedGL = true;
	}
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
