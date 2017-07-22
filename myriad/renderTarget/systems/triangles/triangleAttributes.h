#pragma once

#include "types/vector.h"
#include "types/color.h"

namespace myr
{
	struct TriangleAttributes
	{
		TriangleAttributes(
		const Color &color,
		const Vector &point)
		:color(color), point(point) {}

		union {
			struct {
				Color color;
			};

			float attributeColor[4];
		};

		union {
			struct {
				Vector point;
			};

			float attributePoint[2];
		};
	};
}