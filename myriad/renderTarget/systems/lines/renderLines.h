#pragma once

#include "../renderSystem.h"
#include "lineAttributes.h"

namespace myr
{
	class RenderLines final : public RenderSystem
	{
		friend class Renderer;

	public:
		RenderLines();
		void render(Shader *shader) override;

		static const char *getShaderVertex();
		static const char *getShaderFragment();
		static const std::vector<std::string> getShaderUniforms();

	private:
		void configureBufferAttribs() const;
		void configureInstanceAttribs() const;

		static GLuint buffer;
		static const std::vector<float> getLine();
		static void createBuffer();
		static void freeBuffer();
	};
}