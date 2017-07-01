#include "renderSprites.h"

GLuint myr::RenderSprites::buffer;

const std::vector<myr::Vector> myr::RenderSprites::getQuad()
{
	return std::vector<Vector>({
		Vector(0, 0),
		Vector(0, 1),
		Vector(1, 1),
		Vector(1, 0)
	});
}

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