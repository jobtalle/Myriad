#include "renderSprites.h"
#include "renderer/renderer.h"

#include <iostream>

myr::RenderSprites::RenderSprites()
	:RenderSystem()
{
	glGenBuffers(1, &quad);
	glBindBuffer(GL_ARRAY_BUFFER, quad);
	glBufferData(GL_ARRAY_BUFFER, getQuad().size() * sizeof(Vector), getQuad().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

myr::RenderSprites::~RenderSprites()
{
	glDeleteBuffers(1, &quad);
}

void myr::RenderSprites::flush()
{
	instances.clear();
}

void myr::RenderSprites::render(const RenderBatch &batch, Shader *shader)
{
	RenderSystem::render(batch, shader);

	glUniform1i(shader->getUniformLocation(UNIFORM_ATLAS), Renderer::TextureChannels::ATLAS);

	vaoBind();
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, (GLsizei)(batch.getEnd() - batch.getStart()));
	vaoRelease();
}

void myr::RenderSprites::push(const void *element)
{
	instances.push_back(*((SpriteAttributes*)element));
}

size_t myr::RenderSprites::getBufferIndex() const
{
	return instances.size();
}

size_t myr::RenderSprites::getBufferSizeof() const
{
	return sizeof(SpriteAttributes);
}

const void *myr::RenderSprites::getBufferData() const
{
	return instances.data();
}

void myr::RenderSprites::vaoConfigure()
{
	
}