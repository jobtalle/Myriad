#include "renderRenderTargets.h"
#include "renderer/renderer.h"

#include <iostream> // TODO: Debug

myr::RenderRenderTargets::RenderRenderTargets(const RenderSprites *renderSprites)
:RenderSystem(), instanceCapacity(INSTANCE_CAPACITY_INITIAL), instanceCount(0)
{
	vaoBind();

	renderSprites->configureBufferAttribs();

	bindBuffer();

	renderSprites->configureInstanceAttribs();

	vaoRelease();

	instances = (SpriteAttributes*)malloc(sizeof(SpriteAttributes)* instanceCapacity);
	textures = (GLuint*)malloc(sizeof(GLuint)* instanceCapacity);
}

myr::RenderRenderTargets::~RenderRenderTargets()
{
	free(instances);
	free(textures);
}

void myr::RenderRenderTargets::render(Shader *shader)
{
	shader->bind();

	vaoBind();

	glUniform1i(shader->getUniformLocation(RenderSprites::UNIFORM_ATLAS), Renderer::TextureChannels::RENDER_TARGET);
	glActiveTexture(GL_TEXTURE0 + Renderer::TextureChannels::RENDER_TARGET);

	for(size_t i = 0; i < instanceCount; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);

		const size_t first = i;
		while(i + 1 < instanceCount && textures[i + 1] == textures[first])
			++i;
		
		bindBuffer();

		const size_t batchSize = i - first + 1;
		if(batchSize > bufferCapacity)
		{
			bufferCapacity = batchSize;

			glBufferData(GL_ARRAY_BUFFER, sizeof(SpriteAttributes) * bufferCapacity, NULL, GL_DYNAMIC_DRAW);
		}

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(SpriteAttributes)* first, sizeof(SpriteAttributes) * batchSize, instances + first);
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

		instances = (SpriteAttributes*)realloc(instances, instanceCapacity * sizeof(SpriteAttributes));
		textures = (GLuint*)realloc(textures, instanceCapacity * sizeof(GLuint));
	}

	textures[instanceCount] = ((RenderTargetAttributes*)element)->texture;
	instances[instanceCount++] = ((RenderTargetAttributes*)element)->spriteAttributes;
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