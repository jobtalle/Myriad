#include "renderTarget.h"
#include "../renderer/renderer.h"

#include <iostream> // TODO: Debug

myr::RenderTarget::RenderTarget(const Color &clearColor, const Rect &rect, Renderer *renderer)
	:DefaultRenderTarget(clearColor, rect, renderer)
{
	createRenderSystems();

	generateFBO();
}

myr::RenderTarget::~RenderTarget()
{
	deleteFBO();
}

void myr::RenderTarget::generateFBO()
{
	glGenFramebuffers(1, &fbo);
	glGenTextures(1, &texture);

	resize();

	GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	glDrawBuffers(1, drawBuffers);
}

void myr::RenderTarget::deleteFBO()
{
	glDeleteFramebuffers(1, &fbo);
	glDeleteTextures(1, &texture);
}

void myr::RenderTarget::resize()
{
	glActiveTexture(GL_TEXTURE0 + Renderer::TextureChannels::INTERMEDIATE);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA8,
		rect.getWidth(),
		rect.getHeight(),
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		NULL);
}