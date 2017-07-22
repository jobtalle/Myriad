#include "renderTriangles.h"

myr::RenderTriangles::RenderTriangles()
:RenderSystem(sizeof(TriangleAttributes))
{
	vaoBind();

	bufferBind();

	configureInstanceAttribs();

	vaoRelease();
}

void myr::RenderTriangles::render(Shader *shader)
{
	RenderSystem::render(shader);

	vaoBind();
	glDrawArrays(GL_TRIANGLES, 0, GLsizei(instanceCount));
	vaoRelease();

	instanceCount = 0;
}

void myr::RenderTriangles::configureInstanceAttribs() const
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(TriangleAttributes),
		(GLvoid*)offsetof(TriangleAttributes, color));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TriangleAttributes),
		(GLvoid*)offsetof(TriangleAttributes, point));
}