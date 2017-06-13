#pragma once

#include <vector>

#include "../renderSystem.h"
#include "spriteAttributes.h"
#include "types/vector.h"

namespace myr
{
	class RenderSprites final : public RenderSystem
	{
	public:
		RenderSprites();
		virtual ~RenderSprites();
		void render(Shader *shader) override;
		void push(const void *element) override;
		size_t getBufferIndex() const override;

		static const char *getShaderVertex();
		static const char *getShaderFragment();
		static const std::vector<std::string> getShaderUniforms();

	protected:
		size_t getBufferSizeof() const override;
		const void *getBufferData() const override;

	private:
		static const size_t INSTANCE_CAPACITY_INITIAL = 8;
		static const char *UNIFORM_ATLAS;

		GLuint quad;
		SpriteAttributes *instances;
		size_t instanceCount;
		size_t instanceCapacity;

		static const std::vector<Vector> getQuad();
	};
}