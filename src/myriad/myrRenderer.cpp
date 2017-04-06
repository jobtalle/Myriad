#include "opengl/opengl.h"
#include "myriad/myrRenderer.h"

namespace {
	bool initializedGL;
}

myr::Renderer::Renderer(const Color clearColor, const Rect rect)
:renderTarget(clearColor, rect, this), rect(rect)
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

myr::Rect myr::Renderer::getRect() const
{
	return rect;
}

myr::DefaultRenderTarget &myr::Renderer::getDefaultRenderTarget()
{
	return renderTarget;
}

myr::Shader &myr::Renderer::getDefaultShader()
{
	return defaultShader;
}

myr::Atlas &myr::Renderer::getAtlas()
{
	return atlas;
}