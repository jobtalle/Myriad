#pragma once

#include "myriad/myrVector.h"
#include "quadSpace/quadSpace.h"
#include "opengl/opengl.h"

#include <memory>
#include <string>
#include <map>

namespace myr {
	class Atlas
	{
	public:
		struct Location
		{
			unsigned char atlasIndex;
			Vector location;
			float size;

			Location(
				const unsigned char atlasIndex = 0,
				const Vector location = Vector(0, 0),
				const float size = 0);
		};

		Atlas(const GLuint channel, const unsigned char atom = atomDefault);
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
			std::string name;
			QuadSpace::Node node;

			Entry(const std::string name, const QuadSpace::Node node, const unsigned short width, const unsigned short height);

			Entry() {}

			bool operator < (const struct Entry &entry) const
			{
				return name.compare(entry.name) < 0;
			}
		};

		static const unsigned char atomDefault = 16;
		std::map<std::string, std::shared_ptr<Entry>> entries;
		std::map<std::string, std::shared_ptr<Entry>> unusedEntries;
		QuadSpace tree;
		GLuint texture;
		GLuint channel;
		unsigned char atom;

		void blit(const std::map<std::string, std::shared_ptr<Entry>>::iterator entry, const char *bytes);
		Location entryToLocation(const std::map<std::string, std::shared_ptr<Entry>>::iterator entry) const;
		unsigned char quadSpaceLevel(const unsigned int maxDim) const;
		unsigned char tryAtom(unsigned char atom) const;
		void initializeTexture();
		void allocateTexture();
	};
}