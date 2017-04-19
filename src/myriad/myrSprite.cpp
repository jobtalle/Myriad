#include "myriad/myrSprite.h"
#include "myriad/myrRenderTarget.h"
#include "myriad/myrRenderer.h"

#include <iostream>

myr::Sprite::Sprite()
:flags(UNSET), file(nullptr) {}

myr::Sprite::Sprite(ArchiveFile *file)
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
	const char *bytes = file->getBytes();
	uint32_t width, height;
	
	memcpy(&width, bytes, sizeof(uint32_t));
	memcpy(&height, bytes + sizeof(uint32_t), sizeof(uint32_t));

	flags |= LOADED;

	location = myr::RenderTarget::getCurrent()->getRenderer()->getAtlas().query(
		file->getName(),
		width,
		height,
		bytes + sizeof(uint32_t) * 2);
}