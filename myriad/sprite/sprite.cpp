#include "sprite.h"
#include "renderer/renderer.h"
#include "renderTarget/renderTarget.h"

myr::Sprite::Sprite(
	const std::string &name,
	SpriteDecoder *decoder,
	const Vector &origin)
	:name(name), decoder(decoder), Quad(origin)
{
	load();
}

myr::Sprite::~Sprite()
{
	myr::RenderTarget::getCurrent()->getRenderer()->getAtlas().release(name);
}

void myr::Sprite::draw(
	const Transform &transform) const
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &SpriteAttributes(
		location.location,
		location.size,
		getSize().getSize(),
		origin,
		transform));
}

void myr::Sprite::draw(
	const Transform &transform,
	const Vector &scale) const
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &SpriteAttributes(
		location.location,
		location.size,
		getSize().getSize() * scale,
		origin,
		transform));
}

void myr::Sprite::draw(
	const int x,
	const int y) const
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &SpriteAttributes(
		location.location,
		location.size,
		Vector(x, y),
		getSize().getSize(),
		origin));
}

void myr::Sprite::draw(
	const int x,
	const int y,
	const Vector &scale) const
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &SpriteAttributes(
		location.location,
		location.size,
		Vector(x, y),
		getSize().getSize() * scale,
		origin));
}

void myr::Sprite::draw(
	const int x,
	const int y,
	const Vector &scale,
	const float angle) const
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &SpriteAttributes(
		location.location,
		location.size,
		Vector(x, y),
		getSize().getSize() * scale,
		origin,
		angle));
}

void myr::Sprite::load()
{
	setSize(Rect(decoder->getWidth(), decoder->getHeight()));
	location = myr::RenderTarget::getCurrent()->getRenderer()->getAtlas().query(
		name,
		decoder->getWidth(),
		decoder->getHeight(),
		decoder->getPixels());
}
