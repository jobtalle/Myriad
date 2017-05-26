#include "sprite.h"
#include "renderer/renderer.h"
#include "renderTarget/renderTarget.h"
#include "renderTarget/systems/sprites/spriteAttributes.h"

myr::Sprite::Sprite()
:flags(UNSET), decoder(nullptr) {}

myr::Sprite::Sprite(const std::string name, SpriteDecoder *decoder)
:flags(0), name(name), decoder(decoder) {}

myr::Sprite::~Sprite()
{
	if(!(flags & UNSET) && (flags & LOADED))
	{
		myr::RenderTarget::getCurrent()->getRenderer()->getAtlas().release(name);
	}
}

bool myr::Sprite::isSet() const
{
	return !(flags & UNSET);
}

void myr::Sprite::draw()
{
	if(!(flags & LOADED))
		if(!(flags & UNSET))
			load();

	SpriteAttributes attributes(
		Vector(0, 0),
		Vector(0, 0),
		Vector(0, 0),
		Vector(0, 0));

	RenderTarget::getCurrent()->render(RENDER_SYSTEM_SPRITES, &attributes);
}

void myr::Sprite::load()
{
	flags |= LOADED;

	location = myr::RenderTarget::getCurrent()->getRenderer()->getAtlas().query(
		name,
		decoder->getWidth(),
		decoder->getHeight(),
		decoder->getPixels());
}