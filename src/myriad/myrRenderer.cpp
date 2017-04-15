#include "opengl/opengl.h"
#include "myriad/myrRenderer.h"

#include <iostream>

namespace {
	myr::Renderer *current = nullptr;
}

void myr::initialize()
{
	ogl_LoadFunctions();
}

myr::Renderer::Renderer(const Color clearColor, const Rect rect)
	:renderTarget(clearColor, rect, this), rect(rect), atlas(ATLAS) {}

myr::Renderer::Renderer(const Color clearColor, const Rect rect, const unsigned char atom)
	:renderTarget(clearColor, rect, this), rect(rect), atlas(ATLAS, atom) {}

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

void myr::Renderer::bind()
{
	if(current != this)
	{
		current = this;

		atlas.bind();
		getDefaultShader().bind();
	}
}