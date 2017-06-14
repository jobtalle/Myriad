#include "renderTarget.h"
#include "../renderer/renderer.h"
#include "systems/renderTargets/renderTargetAttributes.h"

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

void myr::RenderTarget::draw(
	const Transform &transform)
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_RENDER_TARGETS, &RenderTargetAttributes(
		SpriteAttributes(
			Vector(0, 1),
			Vector(1, -1),
			rect.getSize(),
			Vector(0, 0),
			transform),
		texture));
}

void myr::RenderTarget::draw(
	const Transform &transform,
	const Vector &scale)
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_RENDER_TARGETS, &RenderTargetAttributes(
		SpriteAttributes(
			Vector(0, 1),
			Vector(1, -1),
			rect.getSize() * scale,
			Vector(0, 0),
			transform),
		texture));
}

void myr::RenderTarget::draw(
	const int x,
	const int y)
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_RENDER_TARGETS, &RenderTargetAttributes(
		SpriteAttributes(
			Vector(0, 1),
			Vector(1, -1),
			Vector(x, y),
			rect.getSize(),
			Vector(0, 0)),
		texture));
}

void myr::RenderTarget::draw(
	const int x,
	const int y,
	const Vector &scale)
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_RENDER_TARGETS, &RenderTargetAttributes(
		SpriteAttributes(
			Vector(0, 1),
			Vector(1, -1),
			Vector(x, y),
			rect.getSize() * scale,
			Vector(0, 0)),
		texture));
}

void myr::RenderTarget::draw(
	const int x,
	const int y,
	const Vector &scale,
	const float angle)
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_RENDER_TARGETS, &RenderTargetAttributes(
		SpriteAttributes(
			Vector(0, 1),
			Vector(1, -1),
			Vector(x, y),
			rect.getSize() * scale,
			Vector(0, 0),
			angle),
		texture));
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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}