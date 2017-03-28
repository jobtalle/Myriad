#pragma once

#include "myrDefaultRenderTarget.h"

namespace myr {
	class RenderTarget : public DefaultRenderTarget
	{
	public:
		RenderTarget(const Color clearColor, const Rect rect);

	private:
		void generateFBO();
		void deleteFBO();
	};
}