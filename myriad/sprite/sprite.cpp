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
	:Quad(origin), currentFrame(0)
{
	load(name, decoder);
}

myr::Sprite::~Sprite()
{
	for(const auto frame : frames)
		myr::RenderTarget::getCurrent()->getRenderer()->getAtlas().release(frame.name);
}

void myr::Sprite::draw(
	const Transform &transform) const
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &SpriteAttributes(
		getLocation(),
		getSize().toVector(),
		getOriginFactor(),
		transform));
}

void myr::Sprite::draw(
	const Transform &transform,
	const Vector &scale) const
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &SpriteAttributes(
		getLocation(),
		getSize().toVector() * scale,
		getOriginFactor(),
		transform));
}

void myr::Sprite::draw(
	const int x,
	const int y) const
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &SpriteAttributes(
		getLocation(),
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
		getLocation(),
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
		getLocation(),
		Vector(x, y),
		getSize().toVector() * scale,
		getOriginFactor(),
		angle));
}

unsigned int myr::Sprite::getFrame() const
{
	return currentFrame;
}

unsigned int myr::Sprite::getFrames() const
{
	return (unsigned int)frames.size();
}

void myr::Sprite::setFrame(const unsigned int frame)
{
#ifdef _DEBUG
	assert(frame < getFrames());
#endif

	this->currentFrame = frame;
}

void myr::Sprite::animate(const float seconds)
{
	if(getFrames() > 1)
	{
		frameCounter += seconds;

		if(frameCounter > frames[getFrame()].duration + seconds * 0.5f)
		{
			while(frameCounter > frames[getFrame()].duration)
			{
				frameCounter -= frames[getFrame()].duration;

				if(++currentFrame == getFrames())
					currentFrame = 0;
			}

			frameCounter = 0;
		}
	}
}

void myr::Sprite::load(const std::string name, myr::SpriteDecoder &decoder)
{
	setSize(Rect(decoder.getFrameWidth(), decoder.getFrameHeight()));

	for(unsigned int frame = 0; frame < decoder.getFrameCount(); ++frame)
	{
		const std::string frameName = std::to_string(frame) + '_' + name;
		const float duration = decoder.getFrameCount() > 1?decoder.getFrameDurations()[frame]:0;
		const FrameData frameData(
			frameName,
			myr::RenderTarget::getCurrent()->getRenderer()->getAtlas().query(
				frameName,
				decoder.getFrameWidth(),
				decoder.getFrameHeight(),
				decoder.getPixels(frame)),
			duration);


		frames.push_back(frameData);
	}
}

const myr::Atlas::Location &myr::Sprite::getLocation() const
{
	return frames[getFrame()].location;
}