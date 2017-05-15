#pragma once

#include "opengl/opengl.h"

#include "myriad/types/myrRect.h"
#include "myriad/types/myrColor.h"

namespace myr {
	class Renderer;

	class DefaultRenderTarget
	{
		friend class Renderer;
		friend class Sprite;

	public:
		DefaultRenderTarget(const Color clearColor, const Rect rect, Renderer *renderer);
		Rect getRect() const;
		void bind();
		void clear() const;
		
	protected:
		Rect rect;
		GLuint fbo;

		void setRect(const Rect rect);
		void unbind();
		Renderer *getRenderer() const;
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