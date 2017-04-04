#pragma once

#include <opengl/opengl.h>

#include "myrRect.h"
#include "myrColor.h"

namespace myr {
	class Renderer;

	class DefaultRenderTarget
	{
		friend class Renderer;

	public:
		DefaultRenderTarget(const Color clearColor, const Rect rect, Renderer *renderer);
		Rect getRect() const;
		Renderer *getRenderer() const;
		void bind();
		void clear() const;
		
	protected:
		Rect rect;
		GLuint fbo;

		void setRect(const Rect rect);
		void unbind();
		static DefaultRenderTarget *getCurrent();

	private:
		Renderer *renderer;
		Color clearColor;
		unsigned char flags;

		void render();

		enum flags {
			BOUND = 0x01
		};
	};
}