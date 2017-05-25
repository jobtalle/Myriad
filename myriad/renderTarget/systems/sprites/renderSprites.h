#pragma once

#include "../renderSystem.h"
#include "spriteAttributes.h"

#include <vector>

namespace myr
{
	class RenderSprites final : public RenderSystem
	{
	public:

	protected:
		size_t getBufferSize() const override;
		const void *getBufferData() const override;

	private:
		std::vector<SpriteAttributes> instances;
	};
}