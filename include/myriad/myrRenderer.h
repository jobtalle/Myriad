#pragma once

#include "myrColor.h"
#include "myrRect.h"
#include "myrDefaultRenderTarget.h"
#include "myrShader.h"
#include "internal/myrAtlas.h"
#include "opengl/opengl.h"

namespace myr {
	class Renderer {
		friend class DefaultRenderTarget;

	public:
		Renderer(const Color clearColor, const Rect rect);
		~Renderer();
		void render();
		void setRect(const Rect rect);
		Rect getRect() const;
		DefaultRenderTarget &getDefaultRenderTarget();
		Shader &getDefaultShader();
		Atlas &getAtlas();

	protected:
		void bind();

	private:
		DefaultRenderTarget renderTarget;
		Shader defaultShader;
		Atlas atlas;
		Rect rect;

		enum textureChannels
		{
			ATLAS         = 0,
			RENDER_TARGET = 1
		};
	};

	void initialize();
}