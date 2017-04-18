#include "myriad/myrSprite.h"
#include "myriad/myrRenderTarget.h"
#include "myriad/myrRenderer.h"

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
	
	location = myr::RenderTarget::getCurrent()->getRenderer()->getAtlas().query(file.getName());
	
	std::cout << location.location.x << ", " << location.location.y << std::endl;
}