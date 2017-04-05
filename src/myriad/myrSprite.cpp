#include "myriad/myrSprite.h"
#include "myriad/myrDefaultRenderTarget.h"

#include <iostream>

myr::Sprite::Sprite()
:flags(UNSET) {}

myr::Sprite::Sprite(const ArchiveFile &file)
:flags(0), file(file) {}

myr::Sprite::~Sprite()
{

}

bool myr::Sprite::isSet() const
{
	return !(flags & UNSET);
}

void myr::Sprite::draw()
{
	if(!(flags & LOADED))
		load();
}

void myr::Sprite::load()
{
	flags |= LOADED;

	myr::DefaultRenderTarget::getCurrent()->getRenderer();
}