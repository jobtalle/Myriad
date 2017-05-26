#include "renderSprites.h"
#include "renderer/renderer.h"

#include <iostream>

void myr::RenderSprites::flush()
{
	RenderSystem::flush();

	instances.clear();
}

void myr::RenderSprites::render(const RenderBatch &batch, Shader *shader)
{
	RenderSystem::render(batch, shader);

	glUniform1i(shader->getUniformLocation(UNIFORM_ATLAS), Renderer::TextureChannels::ATLAS);
}

void myr::RenderSprites::push(const void *element)
{
	instances.push_back(*((SpriteAttributes*)element));
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

void myr::RenderSprites::vaoConfigure()
{

}