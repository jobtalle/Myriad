#pragma once

#include "myrDefaultRenderTarget.h"

namespace myr {
	class RenderTarget : public DefaultRenderTarget
	{
	public:
		RenderTarget(const Rect rect);

	private:
		void generateFBO();
		void deleteFBO();
	};
}