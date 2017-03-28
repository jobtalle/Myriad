#pragma once

#include <opengl/opengl.h>

#include "myrRect.h"
#include "myrColor.h"

namespace myr {
	class DefaultRenderTarget
	{
	public:
		DefaultRenderTarget(const Color clearColor, const Rect rect);
		void setRect(const Rect rect);
		Rect getRect() const;
		void bind();
		void unbind();

	protected:
		Rect rect;
		GLuint fbo;

	private:
		Color clearColor;
		unsigned char flags;

		void render();

		enum flags {
			BOUND = 0x01
		};
	};
}