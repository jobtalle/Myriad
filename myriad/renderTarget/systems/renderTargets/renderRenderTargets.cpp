#include "renderRenderTargets.h"
#include "renderer/renderer.h"

myr::RenderRenderTargets::RenderRenderTargets(const RenderSprites *renderSprites)
:RenderSystem(0), quads(nullptr), textures(nullptr)
{
	vaoBind();

	renderSprites->configureBufferAttribs();

	bufferBind();

	renderSprites->configureInstanceAttribs();

	vaoRelease();
}

myr::RenderRenderTargets::~RenderRenderTargets()
{
	free(quads);
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
		
		bufferBind();

		const size_t batchSize = i - first + 1;
		if(batchSize > bufferCapacity)
		{
			bufferCapacity = batchSize;

			glBufferData(GL_ARRAY_BUFFER, sizeof(SpriteAttributes) * bufferCapacity, NULL, GL_DYNAMIC_DRAW);
		}

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(SpriteAttributes)* first, sizeof(SpriteAttributes)* batchSize, quads + first);
		glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, GLsizei(batchSize));
	}

	instanceCount = 0;

	vaoRelease();
}

void myr::RenderRenderTargets::push(const void *element)
{
	if(ensureCapacity())
	{
		quads = (SpriteAttributes*)realloc(quads, instanceCapacity * sizeof(SpriteAttributes));
		textures = (GLuint*)realloc(textures, instanceCapacity * sizeof(GLuint));
	}

	textures[instanceCount] = ((RenderTargetAttributes*)element)->texture;
	quads[instanceCount++] = ((RenderTargetAttributes*)element)->spriteAttributes;
}