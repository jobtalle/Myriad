#pragma once

#include "myrColor.h"
#include "myrRect.h"
#include "myrDefaultRenderTarget.h"
#include "myrShader.h"

namespace myr {
	class Renderer {
	public:
		Renderer(const Color clearColor, const Rect rect);
		~Renderer();
		void render();
		void setRect(const Rect rect);
		DefaultRenderTarget &getRenderTarget();
		Shader &getDefaultShader();

	private:
		DefaultRenderTarget renderTarget;
		Shader defaultShader;
	};
}