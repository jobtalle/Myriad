#include <myriad/myrDefaultRenderTarget.h>

#include <iostream>
#include <cassert>

namespace {
	static myr::DefaultRenderTarget *current = nullptr;
}

myr::DefaultRenderTarget::DefaultRenderTarget(const Color clearColor, const Rect rect)
	:fbo(0), flags(0), rect(rect), clearColor(clearColor)
{
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

void myr::DefaultRenderTarget::clear() const
{
#ifdef _DEBUG
	assert(flags & BOUND);
#endif

	glClearColor(clearColor.getRed(), clearColor.getGreen(), clearColor.getBlue(), 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void myr::DefaultRenderTarget::render()
{
	
}