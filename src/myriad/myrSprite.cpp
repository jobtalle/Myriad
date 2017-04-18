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

	delete file;
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
	
	flags |= LOADED;
	//for(int i = 0; i < 16; ++i) std::cout << unsigned int(bytes[i]);
	//std::cout << std::endl;
	location = myr::RenderTarget::getCurrent()->getRenderer()->getAtlas().query(
		file->getName(),
		*((uint32_t*)(bytes)),
		*((uint32_t*)(bytes + sizeof(uint32_t))),
		bytes + sizeof(uint32_t) * 2);
	
	//std::cout << location.location.x << ", " << location.location.y << std::endl;
}