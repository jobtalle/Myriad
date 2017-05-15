#pragma once

#include "renderer/opengl/opengl.h"

#include "types/myrRect.h"
#include "types/myrColor.h"

namespace myr
{
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