#include "myrSprite.h"
#include "renderer/myrRenderer.h"
#include "renderTarget/myrRenderTarget.h"

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
	else
	{
		
	}
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