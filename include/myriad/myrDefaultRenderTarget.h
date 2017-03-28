#pragma once

#include <opengl/opengl.h>

#include "myrRect.h"
#include "myrColor.h"

namespace myr {
	class DefaultRenderTarget
	{
		friend class Renderer;

	public:
		DefaultRenderTarget(const Color clearColor, const Rect rect);
		Rect getRect() const;
		void bind();
		void unbind();
		void clear() const;
		
	protected:
		Rect rect;
		GLuint fbo;

		void setRect(const Rect rect);

	private:
		Color clearColor;
		unsigned char flags;

		void render();

		enum flags {
			BOUND = 0x01
		};
	};
}