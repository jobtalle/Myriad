#include "renderSprites.h"

#include <iostream>

void myr::RenderSprites::render(const RenderBatch &batch)
{
	RenderSystem::render(batch);

	
}

void myr::RenderSprites::push(const void *element)
{
	
}

size_t myr::RenderSprites::getBufferIndex() const
{
	return instances.size();
}

size_t myr::RenderSprites::getBufferSize() const
{
	return instances.size() * sizeof(SpriteAttributes);
}

const void *myr::RenderSprites::getBufferData() const
{
	return instances.data();
}