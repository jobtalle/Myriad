#include "renderRenderTargets.h"
#include "renderer/renderer.h"

#include <iostream> // TODO: Debug

/*
void myr::RenderRenderTargets::render(Shader *shader)
{
	shader->bind();

	vaoBind();

	GLuint texLocation = shader->getUniformLocation("texture");

	for(size_t i = 0; i < instanceCount; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + Renderer::TextureChannels::RENDER_TARGET);
		glBindTexture(GL_TEXTURE_2D, 0); // TODO

		glUniform1i(texLocation, Renderer::TextureChannels::RENDER_TARGET);

		glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, 1);
	}

	instanceCount = 0;

	vaoRelease();
}
*/