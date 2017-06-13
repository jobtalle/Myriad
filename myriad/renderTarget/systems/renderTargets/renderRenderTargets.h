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

	protected:
		size_t getBufferIndex() const override;
		size_t getBufferSizeof() const override;
		const void *getBufferData() const override;

	private:
		static const size_t INSTANCE_CAPACITY_INITIAL = 1;

		RenderTargetAttributes *instances;
		size_t instanceCount;
		size_t instanceCapacity;
	};
}