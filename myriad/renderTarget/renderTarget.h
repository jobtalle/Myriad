#pragma once

#include "defaultRenderTarget.h"

namespace myr
{
	class RenderTarget final : public DefaultRenderTarget
	{
	public:
		RenderTarget(const Color &clearColor, const Rect &rect, Renderer *renderer);
		~RenderTarget() override;
		void draw();
		using DefaultRenderTarget::setRect;

	private:
		void generateFBO();
		void deleteFBO();
		void resize();

		GLuint texture;
	};
}