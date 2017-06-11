#pragma once

#include "../renderSystem.h"

namespace myr
{
	class RenderRenderTargets final : public RenderSystem
	{
	public:
		RenderRenderTargets();
		~RenderRenderTargets();
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
	};
}