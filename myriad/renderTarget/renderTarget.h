#pragma once

#include "defaultRenderTarget.h"

namespace myr
{
	class RenderTarget final : public DefaultRenderTarget
	{
	public:
		RenderTarget(const Color &clearColor, const Rect &rect, Renderer *renderer);
		using DefaultRenderTarget::setRect;

	private:
		void generateFBO();
		void deleteFBO();
	};
}