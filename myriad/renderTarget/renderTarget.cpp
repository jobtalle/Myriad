#include "renderTarget.h"

myr::RenderTarget::RenderTarget(const Color &clearColor, const Rect &rect, Renderer *renderer)
	:DefaultRenderTarget(clearColor, rect, renderer)
{
	createRenderSystems();
}

void myr::RenderTarget::generateFBO()
{
	glGenFramebuffers(1, &fbo);
}

void myr::RenderTarget::deleteFBO()
{
	glDeleteFramebuffers(1, &fbo);
}