#include <myriad/myrDefaultRenderTarget.h>

myr::DefaultRenderTarget::DefaultRenderTarget(const Color clearColor, const Rect rect)
	:fbo(0), rect(rect), clearColor(clearColor)
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

GLuint *myr::DefaultRenderTarget::getFbo()
{
	return &fbo;
}

GLuint myr::DefaultRenderTarget::getFbo() const
{
	return fbo;
}

void myr::DefaultRenderTarget::bind() const
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, getFbo());
}

void myr::DefaultRenderTarget::unbind()
{
	// Render batches
}