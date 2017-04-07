#pragma once

#include "quadSpace/quadSpace.h"
#include "opengl/opengl.h"

namespace myr {
	class Atlas
	{
	public:
		Atlas(const GLuint channel, const unsigned char atom = atomDefault);
		~Atlas();
		void bind();

	private:
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