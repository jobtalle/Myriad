#pragma once

#include "myriad/myrVector.h"
#include "quadSpace/quadSpace.h"
#include "opengl/opengl.h"

#include <string>
#include <vector>

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
		Location query(const std::string name);

	private:
		struct Entry
		{
			unsigned int usageCount;
			unsigned short size;
			QuadSpace::Node node;
			std::string name;

			Entry();
			Entry(const std::string name);

			bool operator < (const struct Entry &entry) const
			{
				return name.compare(entry.name) < 0;
			}
		};

		static const unsigned char atomDefault = 16;
		std::vector<Entry> entries;
		QuadSpace tree;
		GLuint texture;
		GLuint channel;
		unsigned char atom;

		unsigned char tryAtom(unsigned char atom) const;
		void initializeTexture();
		void allocateTexture();
	};
}