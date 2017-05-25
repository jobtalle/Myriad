#pragma once

#include "../renderSystem.h"
#include "spriteAttributes.h"

#include <vector>

namespace myr
{
	class RenderSprites final : public RenderSystem
	{
	public:

	private:
		std::vector<SpriteAttributes> instances;
	};
}