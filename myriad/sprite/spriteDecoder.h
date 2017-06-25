#pragma once

#include <cstdint>

namespace myr
{
	class SpriteDecoder
	{
	public:
		virtual ~SpriteDecoder() {};
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		virtual unsigned int getFrameCount() const = 0;
		virtual unsigned int getFrameWidth() const = 0;
		virtual unsigned int getFrameHeight() const = 0;
		virtual float *getFrameDurations() const = 0;
		virtual const char *getPixels() const = 0;

	protected:
		SpriteDecoder() {};
	};
}