#pragma once

#include "../renderSystem.h"
#include "lineAttributes.h"

namespace myr
{
	class RenderLines final : public RenderSystem
	{
	public:
		RenderLines();
		~RenderLines();
		void render(Shader *shader) override;
		void push(const void *element) override;

		static const char *getShaderVertex();
		static const char *getShaderFragment();
		static const std::vector<std::string> getShaderUniforms();

	protected:
		size_t getBufferIndex() const override;
		size_t getBufferSizeof() const override;
		const void *getBufferData() const override;

	private:
		void configureBufferAttribs() const;
		void configureInstanceAttribs() const;
		static const std::vector<float> getLine();

		GLuint line;
		LineAttributes *instances;
		size_t instanceCount;
		size_t instanceCapacity;
	};
}