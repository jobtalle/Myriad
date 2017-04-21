#include "myriad/internal/myrAtlas.h"

#include <iostream>
#include <algorithm>
#include <cmath>
myr::Atlas::Location::Location(const unsigned char atlasIndex, const Vector location, const float size)
	:atlasIndex(atlasIndex), location(location), size(size) {}

myr::Atlas::Entry::Entry(const std::string name)
	:name(name) {}

myr::Atlas::Entry::Entry(const std::string name, const QuadSpace::Node node, const unsigned short width, const unsigned short height)
	:name(name), node(node), width(width), height(height), usageCount(1) {}

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

myr::Atlas::Location myr::Atlas::query(
	const std::string name,
	const unsigned short width,
	const unsigned short height,
	const char *bytes)
{
	auto match = std::lower_bound(entries.begin(), entries.end(), Entry(name));

	if(match == entries.end() || match->name.compare(name) != 0)
	{
		const auto entry = Entry(name, tree.query(quadSpaceLevel(std::max(width, height))), width, height);
		std::cout << "Level " << int(quadSpaceLevel(std::max(width, height))) << std::endl;
		match = entries.insert(
			std::lower_bound(entries.begin(), entries.end(), Entry(name)),
			entry);

		blit(match, bytes);
	}
	else
		++match->usageCount;

	return entryToLocation(match);
}

void myr::Atlas::blit(const std::list<Entry>::iterator entry, const char *bytes)
{
	std::cout << "Blit at " << int(entry->node.getX()) << ", " << int(entry->node.getY()) << std::endl;
}

myr::Atlas::Location myr::Atlas::entryToLocation(const std::list<Entry>::iterator entry) const
{
	return Location(
		0,
		Vector(
			float(entry->node.getX()) / QuadSpace::dimensions,
			float(entry->node.getY()) / QuadSpace::dimensions),
		1);
}

unsigned char myr::Atlas::quadSpaceLevel(const unsigned int maxDim) const
{
	return 7 - unsigned char(ceil(log2(float(maxDim) / atom)));
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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