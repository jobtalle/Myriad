#pragma once

#include "myrColor.h"
#include "myrRect.h"
#include "myrDefaultRenderTarget.h"

namespace myr {
	class Renderer {
	public:
		Renderer(const Color clearColor, const Rect size);
		~Renderer();
		void render() const;

	private:
		DefaultRenderTarget renderTarget;
		Color clearColor;
	};
}