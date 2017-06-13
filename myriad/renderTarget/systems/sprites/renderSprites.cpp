#include "renderSprites.h"
#include "renderer/renderer.h"

#include <iostream>

myr::RenderSprites::RenderSprites()
:RenderSystem(), instanceCapacity(INSTANCE_CAPACITY_INITIAL), instanceCount(0)
{
	vaoBind();

	glGenBuffers(1, &quad);
	glBindBuffer(GL_ARRAY_BUFFER, quad);
	glBufferData(GL_ARRAY_BUFFER, getQuad().size() * sizeof(Vector), getQuad().data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector), NULL);

	bindBuffer();

	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteAttributes),
		(GLvoid*)offsetof(SpriteAttributes, attributeAtlas));

	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteAttributes),
		(GLvoid*)offsetof(SpriteAttributes, attributeScaleRotate));

	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteAttributes),
		(GLvoid*)offsetof(SpriteAttributes, attributeTransform));

	vaoRelease();
	
	instances = (myr::SpriteAttributes*)malloc(sizeof(SpriteAttributes)* instanceCapacity);
}

myr::RenderSprites::~RenderSprites()
{
	free(instances);

	glDeleteBuffers(1, &quad);
}

void myr::RenderSprites::render(Shader *shader)
{
	RenderSystem::render(shader);
	
	glUniform1i(shader->getUniformLocation(UNIFORM_ATLAS), Renderer::TextureChannels::ATLAS);
	
	vaoBind();
	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, (GLsizei)instanceCount);
	vaoRelease();	

	instanceCount = 0;
}

void myr::RenderSprites::push(const void *element)
{
	if(instanceCount == instanceCapacity)
	{
		instanceCapacity <<= 1;

		instances = (SpriteAttributes*)realloc(instances, instanceCapacity * sizeof(SpriteAttributes));
	}

	instances[instanceCount++] = *((SpriteAttributes*)element);
}

size_t myr::RenderSprites::getBufferIndex() const
{
	return instanceCount;
}

size_t myr::RenderSprites::getBufferSizeof() const
{
	return sizeof(SpriteAttributes);
}

const void *myr::RenderSprites::getBufferData() const
{
	return instances;
}