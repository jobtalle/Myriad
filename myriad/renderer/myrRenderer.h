#pragma once

#include "myrAtlas.h"
#include "opengl/opengl.h"
#include "types/myrColor.h"
#include "types/myrRect.h"
#include "shader/myrShader.h"
#include "renderTarget/myrDefaultRenderTarget.h"

#include <memory>

namespace myr {
	class Renderer {
		friend class DefaultRenderTarget;

	public:
		Renderer(const Color clearColor, const Rect rect);
		Renderer(const Color clearColor, const Rect rect, const unsigned char atom);
		~Renderer();
		void render();
		void setRect(const Rect rect);
		Rect getRect() const;
		DefaultRenderTarget &getDefaultRenderTarget();
		Atlas &getAtlas();

	protected:
		enum shaders
		{
			RECT,
			LINE,
			POINT,
			POLY,
			DEFAULT_SHADER_COUNT
		};

		enum textureChannels
		{
			ATLAS,
			RENDER_TARGET
		};

		void bind();
		Shader *getDefaultShader(const enum shaders shader) const;

	private:
		DefaultRenderTarget renderTarget;
		Atlas atlas;
		Rect rect;
		std::auto_ptr<Shader> shaders[DEFAULT_SHADER_COUNT];

		void createDefaultShader();
	};

	void initialize();
}