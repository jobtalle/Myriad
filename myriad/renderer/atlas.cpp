#include "atlas.h"

#include <algorithm>
#include <cmath>

#ifdef _DEBUG
#include <cassert>
#endif

myr::Atlas::Location::Location(const Vector &location, const Vector &size, const unsigned char atlasIndex)
	:location(location), size(size), atlasIndex(atlasIndex) {}

myr::Atlas::Entry::Entry(const QuadSpace::Node node, const unsigned short width, const unsigned short height)
	:node(node), width(width), height(height), usageCount(1) {}

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
	glActiveTexture(GL_TEXTURE0 + channel);
	glBindTexture(GL_TEXTURE_2D, texture);
}

myr::Atlas::Location myr::Atlas::query(
	const std::string &name,
	const unsigned short width,
	const unsigned short height,
	const char *bytes)
{
	auto match = unusedEntries.find(name);

	if(match == unusedEntries.end()) {
		match = entries.find(name);

		if(match == entries.end())
		{
			QuadSpace::Node node = tree.query(quadSpaceLevel(std::max(width, height)));

			while(!node.getValid() && unusedEntries.size())
			{;
				auto remove = unusedEntries.find(unusedEntryNames.front());
				unusedEntryNames.pop_front();

				tree.release(remove->second.get()->node);
				unusedEntries.erase(remove);

				node = tree.query(quadSpaceLevel(std::max(width, height)));
			}

#ifdef _DEBUG
			assert(node.getValid());
#endif

			auto *entry = new Entry(node, width, height);

			match = entries.insert(std::make_pair(name, std::unique_ptr<Entry>(entry))).first;

			blit(match->second.get(), bytes);
		}
		else
			++match->second->usageCount;
	}
	else
	{
		auto recycle = match;

		match = entries.insert(std::make_pair(name, recycle->second)).first;
		++match->second->usageCount;
		
		unusedEntries.erase(recycle);
		unusedEntryNames.remove(name);
	}

	return entryToLocation(match->second.get());
}

void myr::Atlas::release(const std::string &name)
{
	auto match = entries.find(name);
	
	if(--match->second->usageCount == 0) {
		unusedEntries.insert(std::make_pair(name, match->second));
		unusedEntryNames.push_back(name);
		
		entries.erase(match);
	}
}

void myr::Atlas::blit(const struct Entry *entry, const char *bytes)
{
	glActiveTexture(GL_TEXTURE0 + channel);
	glTexSubImage2D(
		GL_TEXTURE_2D,
		0,
		atom * entry->node.getX(),
		atom * entry->node.getY(),
		entry->width,
		entry->height,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		bytes);
}

myr::Atlas::Location myr::Atlas::entryToLocation(const struct Entry *entry) const
{
	return Location(
		Vector(
			float(entry->node.getX()) / QuadSpace::dimensions,
			float(entry->node.getY()) / QuadSpace::dimensions),
		Vector(
			float(entry->width) / (atom * QuadSpace::dimensions),
			float(entry->height) / (atom * QuadSpace::dimensions)),
		0);
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

	return atom > maxAtom?maxAtom:atom;
}

void myr::Atlas::initializeTexture()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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