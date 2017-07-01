#pragma once

#include <vector>

#include "../renderSystem.h"
#include "spriteAttributes.h"
#include "types/vector.h"

namespace myr
{
	class RenderSprites final : public RenderSystem
	{
		friend class RenderRenderTargets;
		friend class Renderer;

	public:
		RenderSprites();
		void render(Shader *shader) override;

		static const char *getShaderVertex();
		static const char *getShaderFragment();
		static const std::vector<std::string> getShaderUniforms();

	private:
		void configureBufferAttribs() const;
		void configureInstanceAttribs() const;

		static const char *UNIFORM_ATLAS;

		static GLuint buffer;
		static const std::vector<Vector> getQuad();
		static void createBuffer();
		static void freeBuffer();
	};
}