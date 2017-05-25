#include "renderSprites.h"

size_t myr::RenderSprites::getBufferSize() const
{
	return instances.size() * sizeof(SpriteAttributes);
}

const void *myr::RenderSprites::getBufferData() const
{
	return instances.data();
}