#pragma once

#include "opengl/opengl.h"
#include "quadSpace/quadSpace.h"
#include "types/myrVector.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace myr
{
	class Atlas final
	{
	public:
		struct Location
		{
			unsigned char atlasIndex;
			Vector location;
			Vector size;

			Location(
				const unsigned char atlasIndex = 0,
				const Vector location = Vector(0, 0),
				const Vector size = Vector(0, 0));
		};

		Atlas(const GLuint channel, const unsigned char atom = 16);
		~Atlas();
		void bind();
		Location query(
			const std::string name,
			const unsigned short width,
			const unsigned short height,
			const char *bytes);
		void release(const std::string name);

	private:
		struct Entry
		{
			unsigned int usageCount;
			unsigned short width;
			unsigned short height;
			QuadSpace::Node node;

			Entry(
				const QuadSpace::Node node,
				const unsigned short width,
				const unsigned short height);
		};

		std::unordered_map<std::string, std::shared_ptr<Entry>> entries;
		std::unordered_map<std::string, std::shared_ptr<Entry>> unusedEntries;
		QuadSpace tree;
		GLuint texture;
		GLuint channel;
		unsigned char atom;

		void blit(const struct Entry *entry, const char *bytes);
		Location entryToLocation(const struct Entry *entry) const;
		unsigned char quadSpaceLevel(const unsigned int maxDim) const;
		unsigned char tryAtom(unsigned char atom) const;
		void initializeTexture();
		void allocateTexture();
	};
}