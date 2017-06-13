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

		bindBuffer();
		glBufferData(GL_ARRAY_BUFFER, sizeof(SpriteAttributes), &instances[i].spriteAttributes, GL_DYNAMIC_DRAW);
		glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, 1);
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