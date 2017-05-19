#pragma once

#include <cstdint>

namespace myr
{
	class SpriteDecoder
	{
	public:
		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;
		virtual const char *getPixels() const = 0;

	protected:
		SpriteDecoder() {};
	};
}