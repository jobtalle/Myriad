#include "renderTriangles.h"

GLuint myr::RenderTriangles::buffer;

const std::vector<float> myr::RenderTriangles::getTriangle()
{
	return std::vector<float>({
		0,
		1,
		2
	});
}

void myr::RenderTriangles::createBuffer()
{
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, getTriangle().size() * sizeof(float), getTriangle().data(), GL_STATIC_DRAW);
}

void myr::RenderTriangles::freeBuffer()
{
	glDeleteBuffers(1, &buffer);
}