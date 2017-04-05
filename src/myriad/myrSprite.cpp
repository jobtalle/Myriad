#include "myriad/myrSprite.h"
#include "myriad/myrDefaultRenderTarget.h"

#include <iostream>

myr::Sprite::Sprite()
:flags(UNSET) {}

myr::Sprite::Sprite(const ArchiveFile &file)
:flags(0), file(file) {}

myr::Sprite::~Sprite()
{
	if(!(flags & UNSET) && (flags & LOADED))
	{
		std::cout << "Release from atlas\n";
	}
}

myr::Sprite &myr::Sprite::operator = (const myr::Sprite &other)
{
	file = other.file;
	flags = other.flags;

	return *this;
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
	std::cout << "Loaded sprite\n";
	myr::DefaultRenderTarget::getCurrent()->getRenderer();
}