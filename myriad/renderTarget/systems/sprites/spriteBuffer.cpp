#include "renderSprites.h"

GLuint myr::RenderSprites::buffer;

void myr::RenderSprites::createBuffer()
{
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, getQuad().size() * sizeof(Vector), getQuad().data(), GL_STATIC_DRAW);
}

void myr::RenderSprites::freeBuffer()
{
	glDeleteBuffers(1, &buffer);
}