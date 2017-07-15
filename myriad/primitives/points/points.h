#pragma once

#include "types/vector.h"
#include "types/color.h"

namespace myr
{
	class Points {
	protected:
		static void drawPoint(
			const myr::Vector &location,
			const myr::Color &color);
	};
}