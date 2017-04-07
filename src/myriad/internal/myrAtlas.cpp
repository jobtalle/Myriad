#include "myriad/internal/myrAtlas.h"

#include <iostream>

myr::Atlas::Atlas(const GLuint channel, const unsigned char atom)
	:channel(channel)
{
	glGenTextures(1, &texture);

	this->atom = tryAtom(atom);
	
	bind();
	initializeTexture();
	allocateTexture();
}

myr::Atlas::~Atlas()
{
	glDeleteTextures(1, &texture);
}

void myr::Atlas::bind()
{
	glActiveTexture(channel);
	glBindTexture(GL_TEXTURE_2D, texture);
}

myr::Atlas::Location myr::Atlas::query(const std::string name)
{
	Location location;

	location.atlasIndex = 0;
	location.location.x = location.location.y;
	location.size = 0;

	//QuadSpace::Node node = tree.query();

	return location;
}

unsigned char myr::Atlas::tryAtom(unsigned char atom) const
{
	GLint maxTextureSize;

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);

	unsigned int maxAtom = maxTextureSize / QuadSpace::dimensions;

	while(atom > maxAtom)
		atom >>= 1;

	return atom;
}

void myr::Atlas::initializeTexture()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void myr::Atlas::allocateTexture()
{
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA8,
		atom * QuadSpace::dimensions,
		atom * QuadSpace::dimensions,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		NULL);
}