#include <opengl/opengl.h>
#include <myriad/myrRenderer.h>

#include <iostream>

namespace {
	bool initializedGL;
}

myr::Renderer::Renderer(const Color clearColor, const Rect rect)
:renderTarget(clearColor, rect, this)
{
	if(!initializedGL)
	{
		ogl_LoadFunctions();
		initializedGL = true;
	}

	getDefaultShader().bind();
}

myr::Renderer::~Renderer()
{
	
}

void myr::Renderer::render()
{
	renderTarget.unbind();
}

void myr::Renderer::setRect(const Rect rect)
{
	renderTarget.setRect(rect);
}

myr::DefaultRenderTarget &myr::Renderer::getRenderTarget()
{
	return renderTarget;
}

myr::Shader &myr::Renderer::getDefaultShader()
{
	return defaultShader;
}