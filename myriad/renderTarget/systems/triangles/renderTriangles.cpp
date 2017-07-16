#include "renderTriangles.h"

myr::RenderTriangles::RenderTriangles()
:RenderSystem(sizeof(TriangleAttributes))
{
	vaoBind();

	configureBufferAttribs();

	bufferBind();

	configureInstanceAttribs();

	vaoRelease();
}

void myr::RenderTriangles::render(Shader *shader)
{
	RenderSystem::render(shader);

	vaoBind();
	glDrawArraysInstanced(GL_TRIANGLES, 0, 3, (GLsizei)instanceCount);
	vaoRelease();

	instanceCount = 0;
}

void myr::RenderTriangles::configureBufferAttribs() const
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(float), NULL);
}

void myr::RenderTriangles::configureInstanceAttribs() const
{
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(TriangleAttributes),
		(GLvoid*)offsetof(TriangleAttributes, attributeColorA));

	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(TriangleAttributes),
		(GLvoid*)offsetof(TriangleAttributes, attributeColorB));

	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(TriangleAttributes),
		(GLvoid*)offsetof(TriangleAttributes, attributeColorC));

	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(TriangleAttributes),
		(GLvoid*)offsetof(TriangleAttributes, attributePointAB));

	glEnableVertexAttribArray(5);
	glVertexAttribDivisor(5, 1);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(TriangleAttributes),
		(GLvoid*)offsetof(TriangleAttributes, attributePointC));
}