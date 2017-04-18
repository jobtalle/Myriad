#include "myriad/internal/myrAtlas.h"

#include <iostream>
#include <algorithm>

myr::Atlas::Location::Location(const unsigned char atlasIndex, const Vector location, const float size)
	:atlasIndex(atlasIndex), location(location), size(size) {}

myr::Atlas::Entry::Entry()
	:usageCount(1) {}

myr::Atlas::Entry::Entry(const std::string name)
	:name(name), usageCount(1) {}

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
	auto match = std::lower_bound(entries.begin(), entries.end(), Entry(name));

	if(match == entries.end() || match->name.compare(name) != 0)
	{
		return Location();
	}
	else
	{
		++match->usageCount;

		return Location(
			0,
			Vector(
				float(match->node.getX()) / QuadSpace::dimensions,
				float(match->node.getY()) / QuadSpace::dimensions),
			1);
	}
	/*
	QuadSpace::Node node = tree.query(7);

	return Location(
		0,
		Vector(float(node.getX()) / QuadSpace::dimensions, float(node.getY()) / QuadSpace::dimensions),
		1);
		*/
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