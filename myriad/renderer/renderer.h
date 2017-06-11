#pragma once

#include "atlas.h"
#include "opengl/opengl.h"
#include "types/color.h"
#include "types/rect.h"
#include "shader/shader.h"
#include "renderTarget/defaultRenderTarget.h"
#include "sharedUniforms.h"

#include <memory>

namespace myr
{
	class Renderer final
	{
		friend class DefaultRenderTarget;
		friend class Shader;
		friend class Sprite;
		friend class RenderSprites;

	public:
		Renderer(const Color &clearColor, const Rect &rect);
		Renderer(const Color &clearColor, const Rect &rect, const unsigned char atom);
		~Renderer();
		void render();
		void setRect(const Rect &rect);
		Rect getRect() const;
		DefaultRenderTarget &getDefaultRenderTarget();

	private:
		enum TextureChannels
		{
			ATLAS,
			RENDER_TARGET
		};

		struct {
			static const char *name() { return "sharedUniforms"; }
			static const GLuint index = 0;

			SharedUniforms data;
			GLuint buffer;
		} sharedUniforms;

		DefaultRenderTarget renderTarget;
		Atlas atlas;
		Rect rect;
		std::shared_ptr<Shader> shaders[RENDER_SYSTEM_COUNT];

		void bind();
		Atlas &getAtlas();
		Shader *getDefaultShader(const enum RenderSystems system) const;
		void createDefaultShaders();
		void initializeUbo();
		void freeUbo();
		void setSharedUniforms(const Rect &rect, const Transform &transform);
	};

	void initialize();
}