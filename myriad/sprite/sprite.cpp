#include "sprite.h"
#include "renderer/renderer.h"
#include "renderTarget/renderTarget.h"
#include "renderTarget/systems/sprites/spriteAttributes.h"

myr::Sprite::Sprite(const std::string name, SpriteDecoder *decoder)
:flags(0), name(name), decoder(decoder) {}

myr::Sprite::~Sprite()
{
	if(flags & LOADED)
		myr::RenderTarget::getCurrent()->getRenderer()->getAtlas().release(name);
}
void myr::Sprite::draw()
{
	if(!(flags & LOADED))
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