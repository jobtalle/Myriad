#include "renderer/opengl/opengl.h"
#include "renderer.h"
#include "renderTarget/systems/sprites/renderSprites.h"
#include "renderTarget/systems/lines/renderLines.h"
#include "renderTarget/systems/points/renderPoints.h"
#include "renderTarget/systems/triangles/renderTriangles.h"

#include <iostream> // TODO: Debug

namespace {
	myr::Renderer *current = nullptr;
}

void myr::initialize()
{
	ogl_LoadFunctions();

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

myr::Renderer::Renderer(const Color &clearColor, const Rect &rect)
:Renderer(clearColor, rect, Atlas::DEFAULT_ATOM) {}

myr::Renderer::Renderer(const Color &clearColor, const Rect &size, const unsigned char atom)
:renderTarget(clearColor, size, this), size(size), atlas(ATLAS, atom)
{
	initializeUbo();

	createBuffers();
	createDefaultShaders();

	renderTarget.createRenderSystems();

	renderTarget.bind();
}

myr::Renderer::~Renderer()
{
	freeBuffers();

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

void myr::Renderer::setSize(const Rect &size)
{
	this->size = size;
}

myr::Rect myr::Renderer::getSize() const
{
	return size;
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

void myr::Renderer::createBuffers() const
{
	RenderSprites::createBuffer();
}

void myr::Renderer::freeBuffers() const
{
	RenderSprites::freeBuffer();
}

void myr::Renderer::createDefaultShaders()
{
	shaders[RENDER_SYSTEM_SPRITES].reset(new Shader(
		RenderSprites::getShaderVertex(),
		RenderSprites::getShaderFragment(),
		RenderSprites::getShaderUniforms(),
		this));

	shaders[RENDER_SYSTEM_RENDER_TARGETS] = shaders[RENDER_SYSTEM_SPRITES];

	shaders[RENDER_SYSTEM_LINES].reset(new Shader(
		RenderLines::getShaderVertex(),
		RenderLines::getShaderFragment(),
		RenderLines::getShaderUniforms(),
		this));

	shaders[RENDER_SYSTEM_POINTS].reset(new Shader(
		RenderPoints::getShaderVertex(),
		RenderPoints::getShaderFragment(),
		RenderPoints::getShaderUniforms(),
		this));

	shaders[RENDER_SYSTEM_TRIANGLES].reset(new Shader(
		RenderTriangles::getShaderVertex(),
		RenderTriangles::getShaderFragment(),
		RenderTriangles::getShaderUniforms(),
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

void myr::Renderer::setSharedUniforms(const Rect &rect, const Transform &transform)
{
	sharedUniforms.data.width = rect.getWidth();
	sharedUniforms.data.row0[0] = transform.row0[0];
	sharedUniforms.data.row0[1] = transform.row0[1];
	sharedUniforms.data.row0[2] = transform.translateX;

	sharedUniforms.data.height = rect.getHeight();
	sharedUniforms.data.row1[0] = transform.row1[0];
	sharedUniforms.data.row1[1] = transform.row1[1];
	sharedUniforms.data.row1[2] = transform.translateY;

	glBindBuffer(GL_UNIFORM_BUFFER, sharedUniforms.buffer);
	glBufferSubData(
		GL_UNIFORM_BUFFER,
		sharedUniforms.index,
		sizeof(sharedUniforms.data),
		&sharedUniforms.data);
	glBindBuffer(GL_UNIFORM_BUFFER, sharedUniforms.index);
}