#include "defaultRenderTarget.h"
#include "renderer/renderer.h"
#include "systems/sprites/renderSprites.h"
#include "systems/renderTargets/renderRenderTargets.h"

#include <cassert>

#include <iostream> // TOOD: Debug

namespace {
	myr::DefaultRenderTarget *current = nullptr;
}

myr::DefaultRenderTarget *myr::DefaultRenderTarget::getCurrent()
{
	return current;
}

myr::DefaultRenderTarget::DefaultRenderTarget(
	const Color &clearColor,
	const Rect &rect,
	Renderer *renderer)
:fbo(0), flags(0), rect(rect), clearColor(clearColor), renderer(renderer), currentSystem(RENDER_SYSTEM_NONE) {}

myr::DefaultRenderTarget::~DefaultRenderTarget()
{
	
}

void myr::DefaultRenderTarget::setRect(const Rect &rect)
{
	this->rect = rect;

	resize();
}

myr::Rect myr::DefaultRenderTarget::getRect() const
{
	return rect;
}

myr::Transform myr::DefaultRenderTarget::getTransform() const
{
	return transform;
}

void myr::DefaultRenderTarget::setTransform(const Transform &transform)
{
	this->transform = transform;

	if(currentSystem != RENDER_SYSTEM_NONE)
	{
		systems[currentSystem].get()->render(shaders[currentSystem]);
		currentSystem = RENDER_SYSTEM_NONE;
	}
}

void myr::DefaultRenderTarget::bind()
{
	if(current)
		current->unbind();
	current = this;
	
	if(flags & BOUND)
		return;
	
	renderer->bind();

	flags |= BOUND;
	
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	glViewport(0, 0, rect.getWidth(), rect.getHeight());
}

void myr::DefaultRenderTarget::unbind()
{
	if(!(flags & BOUND))
		return;

	render();

	flags &= ~BOUND;
}

myr::Renderer *myr::DefaultRenderTarget::getRenderer() const
{
	return renderer;
}

void myr::DefaultRenderTarget::clear() const
{
#ifdef _DEBUG
	assert(flags & BOUND);
#endif

	glClearColor(clearColor.getRed(), clearColor.getGreen(), clearColor.getBlue(), clearColor.getAlpha());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void myr::DefaultRenderTarget::createRenderSystems()
{
	systems[RENDER_SYSTEM_SPRITES].reset(new RenderSprites());
	systems[RENDER_SYSTEM_RENDER_TARGETS].reset(new RenderRenderTargets((RenderSprites*)systems[RENDER_SYSTEM_SPRITES].get()));

	for(size_t i = 0; i < RENDER_SYSTEM_COUNT; ++i)
		shaders[i] = getRenderer()->getDefaultShader(static_cast<RenderSystems>(i));
}

void myr::DefaultRenderTarget::resize()
{

}

void myr::DefaultRenderTarget::render(const RenderSystems system, const void *element)
{
	if(currentSystem != system)
		if(currentSystem == RENDER_SYSTEM_NONE)
			getRenderer()->setSharedUniforms(getRect(), getTransform());
		else
			systems[currentSystem].get()->render(shaders[currentSystem]);

	currentSystem = system;
	systems[currentSystem].get()->push(element);
}

void myr::DefaultRenderTarget::render()
{
	if(currentSystem != RENDER_SYSTEM_NONE)
	{
		systems[currentSystem].get()->render(shaders[currentSystem]);
		currentSystem = RENDER_SYSTEM_NONE;
	}
}