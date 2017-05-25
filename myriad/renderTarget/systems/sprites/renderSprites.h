#pragma once

#include "../renderSystem.h"
#include "spriteAttributes.h"

#include <vector>

namespace myr
{
	class RenderSprites final : public RenderSystem
	{
	public:
		void flush() override;
		void render(const RenderBatch &batch, Shader *shader) override;
		void push(const void *element) override;
		size_t getBufferIndex() const override;

		static const char *getShaderVertex();
		static const char *getShaderFragment();
		static const std::vector<std::string> getShaderUniforms();

	protected:
		size_t getBufferSize() const override;
		const void *getBufferData() const override;

	private:
		std::vector<SpriteAttributes> instances;
	};
}