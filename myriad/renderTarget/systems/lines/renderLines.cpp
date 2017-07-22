#include "renderLines.h"

myr::RenderLines::RenderLines()
:RenderSystem(sizeof(LineAttributes))
{
	vaoBind();

	bufferBind();

	configureInstanceAttribs();

	vaoRelease();
}

void myr::RenderLines::render(Shader *shader)
{
	RenderSystem::render(shader);

	vaoBind();
	glDrawArrays(GL_LINES, 0, GLsizei(instanceCount));
	vaoRelease();

	instanceCount = 0;
}

void myr::RenderLines::configureInstanceAttribs() const
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(LineAttributes),
		(GLvoid*)offsetof(LineAttributes, attributeColor));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(LineAttributes),
		(GLvoid*)offsetof(LineAttributes, attributePoint));
}