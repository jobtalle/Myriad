#include "renderer/opengl/opengl.h"
#include "renderer.h"
#include "renderTarget/systems/sprites/renderSprites.h"

#include <iostream> // TODO: Debug

namespace {
	myr::Renderer *current = nullptr;
}

void myr::initialize()
{
	ogl_LoadFunctions();

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
}

myr::Renderer::Renderer(const Color clearColor, const Rect rect)
:Renderer(clearColor, rect, Atlas::DEFAULT_ATOM) {}

myr::Renderer::Renderer(const Color clearColor, const Rect rect, const unsigned char atom)
:renderTarget(clearColor, rect, this), rect(rect), atlas(ATLAS, atom)
{
	initializeUbo();

	createDefaultShaders();

	renderTarget.createRenderSystems();
}

myr::Renderer::~Renderer()
{
	freeUbo();
}

void myr::Renderer::render()
{
	renderTarget.unbind();

#ifdef _DEBUG
	GLuint err = glGetError();

	if(err != 0)
		std::cout << err << std::endl;
#endif
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

myr::Shader *myr::Renderer::getDefaultShader(const enum RenderSystems system) const
{
	return shaders[system].get();
}

void myr::Renderer::createDefaultShaders()
{
	shaders[RENDER_SYSTEM_SPRITES].reset(new Shader(
		RenderSprites::getShaderVertex(),
		RenderSprites::getShaderFragment(),
		RenderSprites::getShaderUniforms(),
		this));
}

void myr::Renderer::initializeUbo()
{
	glGenBuffers(1, &sharedUniforms.buffer);

	glBindBuffer(GL_UNIFORM_BUFFER, sharedUniforms.buffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(sharedUniforms.data), NULL, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, sharedUniforms.index, sharedUniforms.buffer);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void myr::Renderer::freeUbo()
{
	glDeleteBuffers(1, &sharedUniforms.buffer);
}

void myr::Renderer::setTargetRect(const Rect rect)
{
	sharedUniforms.data.target.width = rect.getWidth();
	sharedUniforms.data.target.height = rect.getHeight();

	glBindBuffer(GL_UNIFORM_BUFFER, sharedUniforms.buffer);
	glBufferSubData(
		GL_UNIFORM_BUFFER,
		sharedUniforms.index,
		sizeof(sharedUniforms.data),
		&sharedUniforms.data);
	glBindBuffer(GL_UNIFORM_BUFFER, sharedUniforms.index);
}