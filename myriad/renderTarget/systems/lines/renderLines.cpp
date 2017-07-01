#include "renderLines.h"

myr::RenderLines::RenderLines()
:RenderSystem(sizeof(LineAttributes))
{
	vaoBind();

	configureBufferAttribs();

	bufferBind();

	configureInstanceAttribs();

	vaoRelease();
}

void myr::RenderLines::render(Shader *shader)
{
	RenderSystem::render(shader);

	vaoBind();
	glDrawArraysInstanced(GL_LINES, 0, 2, (GLsizei)instanceCount);
	vaoRelease();

	instanceCount = 0;
}

void myr::RenderLines::configureBufferAttribs() const
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(float), NULL);
}

void myr::RenderLines::configureInstanceAttribs() const
{
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(LineAttributes),
		(GLvoid*)offsetof(LineAttributes, attributePoints));

	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(LineAttributes),
		(GLvoid*)offsetof(LineAttributes, attributeColor1));

	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(LineAttributes),
		(GLvoid*)offsetof(LineAttributes, attributeColor2));
}