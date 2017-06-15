#pragma once

#include <cstdint>

#include "vector.h"

namespace myr
{
	class Rect final
	{
	public:
		Rect(const uint16_t width, const uint16_t height);
		uint16_t getWidth() const;
		uint16_t getHeight() const;
		Vector toVector() const;
		void setWidth(const uint16_t width);
		void setHeight(const uint16_t height);

	private:
		uint16_t width;
		uint16_t height;
	};
}