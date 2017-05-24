#pragma once

#include "myrAtlas.h"
#include "opengl/opengl.h"
#include "types/myrColor.h"
#include "types/myrRect.h"
#include "shader/myrShader.h"
#include "shader/myrShaderTypes.h"
#include "renderTarget/myrDefaultRenderTarget.h"
#include "myrSharedUniforms.h"

#include <memory>

namespace myr
{
	class Renderer
	{
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

	private:
		enum textureChannels
		{
			ATLAS,
			RENDER_TARGET
		};

		struct {
			SharedUniforms data;
			GLuint buffer;
		} sharedUniforms;

		DefaultRenderTarget renderTarget;
		Atlas atlas;
		Rect rect;
		std::auto_ptr<Shader> shaders[ShaderType::COUNT];

		void bind();
		Shader *getDefaultShader(const enum ShaderType type) const;
		void createDefaultShaders();
		void initializeUbo();
		void freeUbo();
	};

	void initialize();
}