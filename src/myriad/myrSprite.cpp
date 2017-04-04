#include <myriad/myrSprite.h>
#include <myriad/myrDefaultRenderTarget.h>

myr::Sprite::Sprite(Archive *archive, const std::string name)
:flags(0)
{
	
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