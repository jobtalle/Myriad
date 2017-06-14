#include "renderRenderTargets.h"
#include "renderer/renderer.h"

#include <iostream> // TODO: Debug

myr::RenderRenderTargets::RenderRenderTargets(const RenderSprites *renderSprites)
:RenderSystem(), instanceCapacity(INSTANCE_CAPACITY_INITIAL), instanceCount(0)
{
	vaoBind();

	glBindBuffer(GL_ARRAY_BUFFER, renderSprites->quad);

	renderSprites->configureQuadAttribs();

	bindBuffer();

	renderSprites->configureSpriteAttribs();

	vaoRelease();

	instances = (RenderTargetAttributes*)malloc(sizeof(RenderTargetAttributes)* instanceCapacity);
}

myr::RenderRenderTargets::~RenderRenderTargets()
{
	free(instances);
}

void myr::RenderRenderTargets::render(Shader *shader)
{
	shader->bind();

	vaoBind();

	glUniform1i(shader->getUniformLocation(RenderSprites::UNIFORM_ATLAS), Renderer::TextureChannels::RENDER_TARGET);
	glActiveTexture(GL_TEXTURE0 + Renderer::TextureChannels::RENDER_TARGET);

	for(size_t i = 0; i < instanceCount; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, instances[i].texture);

		const size_t first = i;

		while(i + 1 < instanceCount && instances[i + 1].texture == instances[first].texture)
			++i;
		
		bindBuffer();

		const size_t batchSize = i - first + 1;
		if(batchSize > bufferCapacity)
		{
			bufferCapacity = batchSize;

			glBufferData(GL_ARRAY_BUFFER, sizeof(SpriteAttributes) * bufferCapacity, NULL, GL_DYNAMIC_DRAW);
		}

		for(size_t j = 0; j < batchSize; ++j)
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(SpriteAttributes)* (first + j), sizeof(SpriteAttributes), &instances[first + j].spriteAttributes);

		glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, GLsizei(batchSize));
	}

	instanceCount = 0;

	vaoRelease();
}

void myr::RenderRenderTargets::push(const void *element)
{
	if(instanceCount == instanceCapacity)
	{
		instanceCapacity <<= 1;

		instances = (RenderTargetAttributes*)realloc(instances, instanceCapacity * sizeof(RenderTargetAttributes));
	}

	instances[instanceCount++] = *((RenderTargetAttributes*)element);
}

size_t myr::RenderRenderTargets::getBufferIndex() const
{
	return 0;
}

size_t myr::RenderRenderTargets::getBufferSizeof() const
{
	return 0;
}

const void *myr::RenderRenderTargets::getBufferData() const
{
	return 0;
}