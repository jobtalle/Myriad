#include "myriad/internal/myrAtlas.h"

#include <iostream>
#include <algorithm>
#include <cmath>

myr::Atlas::Location::Location(const unsigned char atlasIndex, const Vector location, const float size)
	:atlasIndex(atlasIndex), location(location), size(size) {}

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
	auto recycle = unusedEntries.find(name);
	std::map<std::string, std::shared_ptr<Entry>>::iterator match;

	if(recycle == unusedEntries.end()) {
		match = entries.find(name);

		if(match == entries.end())
		{
			auto *entry = new Entry(
				name,
				tree.query(quadSpaceLevel(std::max(width, height))), width, height);

			match = entries.insert(
				entries.lower_bound(name),
				std::make_pair(name, std::auto_ptr<Entry>(entry)));
			blit(match, bytes);
		}
		else
			++match->second->usageCount;
	}
	else
	{
		match = entries.insert(entries.lower_bound(name), std::make_pair(name, recycle->second));
		++match->second->usageCount;
		
		unusedEntries.erase(recycle);
	}

	std::cout << int(match->second->node.getX()) << ", " << int(match->second->node.getY()) << std::endl;

	return entryToLocation(match);
}

void myr::Atlas::release(const std::string name)
{
	auto match = entries.find(name);
	
	if(--match->second->usageCount == 0) {
		unusedEntries.insert(unusedEntries.lower_bound(name), std::make_pair(name, match->second));
		
		entries.erase(match);
	}
}

void myr::Atlas::blit(const std::map<std::string, std::shared_ptr<Entry>>::iterator entry, const char *bytes)
{
	glActiveTexture(channel);
	glTexSubImage2D(
		GL_TEXTURE_2D,
		0,
		atom * entry->second->node.getX(),
		atom * entry->second->node.getY(),
		entry->second->width,
		entry->second->height,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		bytes);
}

myr::Atlas::Location myr::Atlas::entryToLocation(const std::map<std::string, std::shared_ptr<Entry>>::iterator entry) const
{
	return Location(
		0,
		Vector(
			float(entry->second->node.getX()) / QuadSpace::dimensions,
			float(entry->second->node.getY()) / QuadSpace::dimensions),
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

	// Todo: use log
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