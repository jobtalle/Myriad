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
		void bind() const;
		void unbind();

	protected:
		Rect rect;

		GLuint *getFbo();
		GLuint getFbo() const;

	private:
		Color clearColor;
		GLuint fbo;
	};
}