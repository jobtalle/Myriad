#pragma once

#include "renderTargetAttributes.h"
#include "../sprites/renderSprites.h"
#include "../renderSystem.h"

namespace myr
{
	class RenderRenderTargets final : public RenderSystem
	{
	public:
		RenderRenderTargets(const RenderSprites *renderSprites);
		~RenderRenderTargets();
		void render(Shader *shader) override;
		void push(const void *element) override;

	private:
		SpriteAttributes *quads;
		GLuint *textures;
	};
}