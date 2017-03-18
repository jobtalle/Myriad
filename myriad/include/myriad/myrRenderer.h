#pragma once

#include "myrColor.h"

namespace myr {
	class Renderer {
		Color clearColor;

	public:
		Renderer(const Color clearColor);
		~Renderer();
		void render() const;
	};
}