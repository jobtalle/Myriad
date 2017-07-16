#pragma once

#include "../renderSystem.h"
#include "pointAttributes.h"

namespace myr
{
	class RenderPoints final : public RenderSystem
	{
		friend class Renderer;

	public:
		RenderPoints();
		void render(Shader *shader) override;

		static const char *getShaderVertex();
		static const char *getShaderFragment();
		static const std::vector<std::string> getShaderUniforms();

	private:
		void configureInstanceAttribs() const;
	};
}