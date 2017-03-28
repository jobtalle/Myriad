#include <myriad/myrRenderTarget.h>

myr::RenderTarget::RenderTarget(const Rect rect)
{
	setRect(rect);
}

void myr::RenderTarget::generateFBO()
{
	glGenFramebuffers(1, getFbo());
}

void myr::RenderTarget::deleteFBO()
{
	glDeleteFramebuffers(1, getFbo());
}