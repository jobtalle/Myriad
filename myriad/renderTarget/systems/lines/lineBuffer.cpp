#include "renderLines.h"

GLuint myr::RenderLines::buffer;

void myr::RenderLines::createBuffer()
{
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, getLine().size() * sizeof(float), getLine().data(), GL_STATIC_DRAW);
}

void myr::RenderLines::freeBuffer()
{
	glDeleteBuffers(1, &buffer);
}