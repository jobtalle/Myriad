#include "defaultRenderTarget.h"
#include "renderer/renderer.h"
#include "systems/sprites/renderSprites.h"

#include <cassert>

#include <iostream> // TOOD: Debug

namespace {
	myr::DefaultRenderTarget *current = nullptr;
}

myr::DefaultRenderTarget *myr::DefaultRenderTarget::getCurrent()
{
	return current;
}

myr::DefaultRenderTarget::DefaultRenderTarget(const Color clearColor, const Rect rect, Renderer *renderer)
:fbo(0), flags(0), rect(rect), clearColor(clearColor), renderer(renderer)
{
	createRenderSystems();
}

void myr::DefaultRenderTarget::setRect(const Rect rect)
{
	this->rect = rect;
}

myr::Rect myr::DefaultRenderTarget::getRect() const
{
	return rect;
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

void myr::DefaultRenderTarget::render(const RenderSystems system, const void *element)
{
	if(batches.empty() || batches.front().getType() != system)
	{
		batches.push(RenderBatch(system, systems[system].get()->getBufferIndex()));
	}
	else
		batches.front().increment();

	systems[system].get()->push(element);
}

void myr::DefaultRenderTarget::render()
{
	std::vector<RenderSystems> usedSystems;

	getRenderer()->setTargetRect(getRect());

	while(!batches.empty())
	{
		if(std::find(
			usedSystems.begin(),
			usedSystems.end(),
			batches.front().getType()) == usedSystems.end())
			usedSystems.push_back(batches.front().getType());

		systems[batches.front().getType()].get()->render(batches.front());
		batches.pop();
	}

	for(auto i = usedSystems.begin(); i != usedSystems.end(); ++i)
		systems[*i].get()->flush();
}

void myr::DefaultRenderTarget::createRenderSystems()
{
	systems[RENDER_SYSTEM_SPRITES].reset(new RenderSprites());
}