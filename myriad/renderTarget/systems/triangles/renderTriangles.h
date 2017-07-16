#pragma once

#include "../renderSystem.h"
#include "triangleAttributes.h"

namespace myr
{
	class RenderTriangles final : public RenderSystem
	{
		friend class Renderer;

	public:
		RenderTriangles();
		void render(Shader *shader) override;

		static const char *getShaderVertex();
		static const char *getShaderFragment();
		static const std::vector<std::string> getShaderUniforms();

	private:
		void configureBufferAttribs() const;
		void configureInstanceAttribs() const;

		static GLuint buffer;
		static const std::vector<float> getTriangle();
		static void createBuffer();
		static void freeBuffer();
	};
}