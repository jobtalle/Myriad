#pragma once

#include <cstdint>

#include "myrRect.h"

namespace myr {
	class Sprite {
	public:
		Sprite(const Rect size, const char *image);
		~Sprite();

	private:
		uint8_t flags;
		const Rect size;
		char *pixels;

		enum flags {
			UPLOADED = 0x01
		};
	};
}