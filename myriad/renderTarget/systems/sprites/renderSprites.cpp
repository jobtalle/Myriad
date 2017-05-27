#include "renderSprites.h"
#include "renderer/renderer.h"

#include <iostream>

myr::RenderSprites::RenderSprites()
	:RenderSystem()
{
	vaoBind();

	glGenBuffers(1, &quad);
	glBindBuffer(GL_ARRAY_BUFFER, quad);
	glBufferData(GL_ARRAY_BUFFER, getQuad().size() * sizeof(Vector), getQuad().data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribDivisor(0, 0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector), NULL);

	bindBuffer();

	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteAttributes),
		(GLvoid*)offsetof(SpriteAttributes, attributeAtlas));

	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteAttributes),
		(GLvoid*)offsetof(SpriteAttributes, attributeLocation));

	vaoRelease();
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
	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, (GLsizei)(batch.getEnd() - batch.getStart()));
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	vaoRelease();

	/*
	glBindBuffer(GL_ARRAY_BUFFER, quad);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector), NULL);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/
	
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