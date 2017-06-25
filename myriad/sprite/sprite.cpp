#include "sprite.h"
#include "renderer/renderer.h"
#include "renderTarget/renderTarget.h"

myr::Sprite::Sprite(
	const std::string &name,
	SpriteDecoder *decoder,
	const Vector &origin)
	:name(name), decoder(decoder), Quad(origin), frame(0)
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
		getLocation().location,
		getLocation().size,
		getSize().toVector(),
		getOriginFactor(),
		transform));
}

void myr::Sprite::draw(
	const Transform &transform,
	const Vector &scale) const
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &SpriteAttributes(
		getLocation().location,
		getLocation().size,
		getSize().toVector() * scale,
		getOriginFactor(),
		transform));
}

void myr::Sprite::draw(
	const int x,
	const int y) const
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &SpriteAttributes(
		getLocation().location,
		getLocation().size,
		Vector(x, y),
		getSize().toVector(),
		getOriginFactor()));
}

void myr::Sprite::draw(
	const int x,
	const int y,
	const Vector &scale) const
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &SpriteAttributes(
		getLocation().location,
		getLocation().size,
		Vector(x, y),
		getSize().toVector() * scale,
		getOriginFactor()));
}

void myr::Sprite::draw(
	const int x,
	const int y,
	const Vector &scale,
	const float angle) const
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &SpriteAttributes(
		getLocation().location,
		getLocation().size,
		Vector(x, y),
		getSize().toVector() * scale,
		getOriginFactor(),
		angle));
}

unsigned int myr::Sprite::getFrame() const
{
	return (unsigned int)frame;
}

unsigned int myr::Sprite::getFrames() const
{
	return (unsigned int)locations.size();
}

void myr::Sprite::setFrame(const unsigned int frame)
{
	this->frame = (float)frame;
}

void myr::Sprite::animate(const float seconds)
{
	frame += seconds;

	while((unsigned int)frame > getFrames())
		frame -= getFrames();
}

void myr::Sprite::load()
{
	setSize(Rect(decoder->getWidth(), decoder->getHeight()));
	locations.push_back(myr::RenderTarget::getCurrent()->getRenderer()->getAtlas().query(
		name,
		decoder->getWidth(),
		decoder->getHeight(),
		decoder->getPixels()));
}

const myr::Atlas::Location &myr::Sprite::getLocation() const
{
	return locations[getFrame()];
}