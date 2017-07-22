#include "renderPoints.h"

myr::RenderPoints::RenderPoints()
:RenderSystem(sizeof(PointAttributes))
{
	vaoBind();

	bufferBind();

	configureInstanceAttribs();

	vaoRelease();
}

void myr::RenderPoints::render(Shader *shader)
{
	RenderSystem::render(shader);

	vaoBind();
	glDrawArrays(GL_POINTS, 0, GLsizei(instanceCount));
	vaoRelease();

	instanceCount = 0;
}

void myr::RenderPoints::configureInstanceAttribs() const
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(PointAttributes),
		(GLvoid*)offsetof(PointAttributes, attributeColor));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(PointAttributes),
		(GLvoid*)offsetof(PointAttributes, attributePoint));
}