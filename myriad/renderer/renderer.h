#pragma once

#include "atlas.h"
#include "opengl/opengl.h"
#include "types/color.h"
#include "types/rect.h"
#include "shader/shader.h"
#include "shader/shaderTypes.h"
#include "renderTarget/defaultRenderTarget.h"
#include "sharedUniforms.h"

#include <memory>

namespace myr
{
	class Renderer final
	{
		friend class DefaultRenderTarget;
		friend class Shader;

	public:
		Renderer(const Color clearColor, const Rect rect);
		Renderer(const Color clearColor, const Rect rect, const unsigned char atom);
		~Renderer();
		void render();
		void setRect(const Rect rect);
		Rect getRect() const;
		DefaultRenderTarget &getDefaultRenderTarget();
		Atlas &getAtlas();

	private:
		enum textureChannels
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
		std::unique_ptr<Shader> shaders[ShaderType::COUNT];

		void bind();
		Shader *getDefaultShader(const enum ShaderType type) const;
		void createDefaultShaders();
		void initializeUbo();
		void freeUbo();
		void setTargetRect(const Rect rect);
	};

	void initialize();
}