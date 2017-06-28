#include "sprite.h"
#include "renderer/renderer.h"
#include "renderTarget/renderTarget.h"

#include <string>

#ifdef _DEBUG
#include <cassert>
#endif

myr::Sprite::Sprite(
	const std::string &name,
	SpriteDecoder &decoder,
	const Vector &origin)
	:Quad(origin), frame(0)
{
	load(name, decoder);
}

myr::Sprite::~Sprite()
{
	for(const auto name : names)
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
	return frame;
}

unsigned int myr::Sprite::getFrames() const
{
	return (unsigned int)locations.size();
}

void myr::Sprite::setFrame(const unsigned int frame)
{
#ifdef _DEBUG
	assert(frame < getFrames());
#endif

	this->frame = frame;
}

void myr::Sprite::animate(const float seconds)
{
	if(getFrames() > 1)
	{
		frameCounter += seconds;

		while(frameCounter > frameDurations.get()[getFrame()])
		{
			frameCounter -= frameDurations.get()[getFrame()];

			if(++frame == getFrames())
				frame = 0;
		}
	}
}

void myr::Sprite::load(const std::string name, myr::SpriteDecoder &decoder)
{
	setSize(Rect(decoder.getFrameWidth(), decoder.getFrameHeight()));

	if(decoder.getFrameCount() > 1)
	{
		frameDurations.reset(new float[decoder.getFrameCount()]);

		memcpy(frameDurations.get(), decoder.getFrameDurations(), sizeof(float)* decoder.getFrameCount());
	}

	for(unsigned int frame = 0; frame < decoder.getFrameCount(); ++frame)
	{
		const std::string frameName = std::to_string(frame) + '_' + name;

		names.push_back(frameName);
		locations.push_back(myr::RenderTarget::getCurrent()->getRenderer()->getAtlas().query(
			frameName,
			decoder.getFrameWidth(),
			decoder.getFrameHeight(),
			decoder.getPixels(frame)));
	}
}

const myr::Atlas::Location &myr::Sprite::getLocation() const
{
	return locations[getFrame()];
}