#pragma once

#include "myrColor.h"
#include "myrRect.h"

#include "myrDefaultRenderTarget.h"

namespace myr {
	class Renderer {
	public:
		Renderer(const Color clearColor, const Rect rect);
		~Renderer();
		void render();
		void setRect(const Rect rect);
		Rect getRect() const;
		DefaultRenderTarget &getRenderTarget();

	private:
		DefaultRenderTarget renderTarget;
	};
}