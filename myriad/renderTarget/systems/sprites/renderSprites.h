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
		~RenderSprites();
		void render(Shader *shader) override;
		void push(const void *element) override;

		static const char *getShaderVertex();
		static const char *getShaderFragment();
		static const std::vector<std::string> getShaderUniforms();

	protected:
		size_t getBufferIndex() const override;
		size_t getBufferSizeof() const override;
		const void *getBufferData() const override;

	private:
		void configureBufferAttribs() const;
		void configureInstanceAttribs() const;

		static const char *UNIFORM_ATLAS;

		static GLuint buffer;
		static const std::vector<Vector> getQuad();
		static void createBuffer();
		static void freeBuffer();

		SpriteAttributes *instances;
		size_t instanceCount;
		size_t instanceCapacity;
	};
}