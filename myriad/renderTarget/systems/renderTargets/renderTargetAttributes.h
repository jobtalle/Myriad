#pragma once

#include "../sprites/spriteAttributes.h"
#include "renderer/opengl/opengl.h"

namespace myr
{
	struct RenderTargetAttributes
	{
		RenderTargetAttributes(
			const SpriteAttributes &spriteAttributes,
			const GLuint texture)
			:spriteAttributes(spriteAttributes), texture(texture) {}

		GLuint texture;
		SpriteAttributes spriteAttributes;
	};
}