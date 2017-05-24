#include "renderer/opengl/opengl.h"
#include "myrRenderer.h"

#include <iostream> // TODO: Debug

namespace {
	myr::Renderer *current = nullptr;
}

void myr::initialize()
{
	ogl_LoadFunctions();
}

myr::Renderer::Renderer(const Color clearColor, const Rect rect)
:renderTarget(clearColor, rect, this), rect(rect), atlas(ATLAS)
{
	initializeUbo();
}

myr::Renderer::Renderer(const Color clearColor, const Rect rect, const unsigned char atom)
:renderTarget(clearColor, rect, this), rect(rect), atlas(ATLAS, atom)
{
	initializeUbo();
}

myr::Renderer::~Renderer()
{
	freeUbo();
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
	}
}

myr::Shader *myr::Renderer::getDefaultShader(const enum ShaderType type) const
{
	return shaders[type].get();
}

void myr::Renderer::createDefaultShaders()
{
	// TODO
}

void myr::Renderer::initializeUbo()
{
	glGenBuffers(1, &sharedUniforms.buffer);

	glBindBuffer(GL_UNIFORM_BUFFER, sharedUniforms.buffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(sharedUniforms.data), NULL, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, sharedUniforms.buffer);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void myr::Renderer::freeUbo()
{
	glDeleteBuffers(1, &sharedUniforms.buffer);
}