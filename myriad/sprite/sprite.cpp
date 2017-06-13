#include "sprite.h"
#include "renderer/renderer.h"
#include "renderTarget/renderTarget.h"
#include "renderTarget/systems/sprites/spriteAttributes.h"

myr::Sprite::Sprite(
	const std::string &name,
	SpriteDecoder *decoder,
	const int originX,
	const int originY)
	:name(name), decoder(decoder), originX(originX), originY(originY), origin(0, 0)
{
	load();
}

myr::Sprite::~Sprite()
{
	myr::RenderTarget::getCurrent()->getRenderer()->getAtlas().release(name);
}

void myr::Sprite::draw(
	const Transform &transform)
{
	SpriteAttributes attributes(
		location.location,
		location.size,
		Vector(width, height),
		origin,
		transform);

	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &attributes);
}

void myr::Sprite::draw(
	const Transform &transform,
	const Vector &scale)
{
	SpriteAttributes attributes(
		location.location,
		location.size,
		Vector(width * scale.x, height * scale.y),
		origin,
		transform);

	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &attributes);
}

void myr::Sprite::draw(
	const int x,
	const int y)
{
	SpriteAttributes attributes(
		location.location,
		location.size,
		Vector(x, y),
		Vector(width, height),
		origin);

	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &attributes);
}

void myr::Sprite::draw(
	const int x,
	const int y,
	const Vector &scale)
{
	SpriteAttributes attributes(
		location.location,
		location.size,
		Vector(x, y),
		Vector(width * scale.x, height * scale.y),
		origin);

	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &attributes);
}

void myr::Sprite::draw(
	const int x,
	const int y,
	const Vector &scale,
	const float angle)
{
	SpriteAttributes attributes(
		location.location,
		location.size,
		Vector(x, y),
		Vector(width * scale.x, height * scale.y),
		origin,
		angle);

	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &attributes);
}

void myr::Sprite::setOrigin(const int originX, const int originY)
{
	this->originX = originX;
	this->originY = originY;
}

short int myr::Sprite::getWidth() const
{
	return width;
}

short int myr::Sprite::getHeight() const
{
	return height;
}

int myr::Sprite::getOriginX() const
{
	return originX;
}

int myr::Sprite::getOriginY() const
{
	return originY;
}

void myr::Sprite::load()
{
	width = decoder->getWidth();
	height = decoder->getHeight();
	origin = Vector(float(originX) / width, float(originY) / height);
	location = myr::RenderTarget::getCurrent()->getRenderer()->getAtlas().query(
		name,
		decoder->getWidth(),
		decoder->getHeight(),
		decoder->getPixels());
}
