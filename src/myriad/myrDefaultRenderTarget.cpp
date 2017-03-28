#include <myriad/myrDefaultRenderTarget.h>

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
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

	flags |= BOUND;
}

void myr::DefaultRenderTarget::unbind()
{
	if(!(flags & BOUND))
	{
		render();

		flags &= ~BOUND;
	}
}

void myr::DefaultRenderTarget::render()
{
	glClearColor(clearColor.getRed(), clearColor.getGreen(), clearColor.getBlue(), 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}