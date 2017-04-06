#pragma once

#include "myrColor.h"
#include "myrRect.h"
#include "myrDefaultRenderTarget.h"
#include "myrShader.h"
#include "internal/myrAtlas.h"

namespace myr {
	class Renderer {
	public:
		Renderer(const Color clearColor, const Rect rect);
		~Renderer();
		void render();
		void setRect(const Rect rect);
		Rect getRect() const;
		DefaultRenderTarget &getDefaultRenderTarget();
		Shader &getDefaultShader();
		Atlas &getAtlas();

	private:
		DefaultRenderTarget renderTarget;
		Shader defaultShader;
		Atlas atlas;
		Rect rect;
	};
}