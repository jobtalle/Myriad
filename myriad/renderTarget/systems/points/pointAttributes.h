#pragma once

#include "types/vector.h"
#include "types/color.h"

namespace myr
{
	struct PointAttributes
	{
		PointAttributes(
			const Vector &point,
			const Color &color)
			:point(point), color(color) {}

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