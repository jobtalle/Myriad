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
			Location();

			unsigned char atlasIndex;
			Vector location;
			float size;
		};

		Atlas(const GLuint channel, const unsigned char atom = atomDefault);
		~Atlas();
		void bind();
		Location query(const std::string name);

	private:
		struct Entry
		{
			QuadSpace::Node node;
			std::string name;

			bool operator < (const struct Entry &entry) const
			{
				return name.compare(entry.name) < 0;
			}
		};

		static const unsigned char atomDefault = 16;
		QuadSpace tree;
		GLuint texture;
		GLuint channel;
		unsigned char atom;

		unsigned char tryAtom(unsigned char atom) const;
		void initializeTexture();
		void allocateTexture();
	};
}