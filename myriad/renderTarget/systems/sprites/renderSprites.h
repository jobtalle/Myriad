#pragma once

#include "../renderSystem.h"
#include "spriteAttributes.h"
#include "types/vector.h"

#include <vector>

namespace myr
{
	class RenderSprites final : public RenderSystem
	{
	public:
		RenderSprites();
		~RenderSprites();
		void flush() override;
		void render(const RenderBatch &batch, Shader *shader) override;
		void push(const void *element) override;
		size_t getBufferIndex() const override;

		static const char *getShaderVertex();
		static const char *getShaderFragment();
		static const std::vector<std::string> getShaderUniforms();

	protected:
		size_t getBufferSizeof() const override;
		const void *getBufferData() const override;
		void vaoConfigure() override;

	private:
		static const char *UNIFORM_ATLAS;
		GLuint quad;
		std::vector<SpriteAttributes> instances;

		static const std::vector<Vector> getQuad();
	};
}