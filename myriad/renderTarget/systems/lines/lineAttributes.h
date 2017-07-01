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
			const Color &color1,
			const Color &color2)
			:start(start), end(end), color1(color1), color2(color2) {}

		union {
			struct {
				Vector start;
				Vector end;
			};

			float attributePoints[4];
		};

		union {
			struct {
				Color color1;
			};

			float attributeColor1[4];
		};

		union {
			struct {
				Color color2;
			};

			float attributeColor2[4];
		};
	};
}