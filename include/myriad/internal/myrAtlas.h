#pragma once

#include "quadSpace/quadSpace.h"
#include "opengl/opengl.h"

namespace myr {
	class Atlas
	{
	public:
		Atlas(const GLuint channel);
		~Atlas();
		void bind();

	private:
		QuadSpace tree;
		GLuint texture;
		GLuint channel;

		void initializeTexture();
	};
}