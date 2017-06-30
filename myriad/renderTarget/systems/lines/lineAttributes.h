#pragma once

#include "types/vector.h"
#include "types/color.h"

namespace myr
{
	struct LineAttributes
	{
		LineAttributes(
			const Vector &start,
			const Vector &end,
			const Color &color)
			:start(start), end(end), color(color)
		{

		}

		union {
			struct {
				Vector start;
				Vector end;
			};

			float attributePoints[4];
		};

		union {
			struct {
				Color color;
			};

			float attributeColor[4];
		};
	};
}