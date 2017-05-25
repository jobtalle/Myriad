#pragma once

#include "../myrRenderSystem.h"
#include "myrSpriteAttributes.h"

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