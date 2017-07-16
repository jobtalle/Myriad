#pragma once

#include "types/vector.h"
#include "types/color.h"

namespace myr
{
	struct TriangleAttributes
	{
		TriangleAttributes(
		const Vector &pointA,
		const Vector &pointB,
		const Vector &pointC,
		const Color &colorA,
		const Color &colorB,
		const Color &colorC)
		:pointA(pointA), pointB(pointB), pointC(pointC), colorA(colorA), colorB(colorB), colorC(colorC) {}

		union {
			struct {
				Color colorA;
			};

			float attributeColorA[4];
		};

		union {
			struct {
				Color colorB;
			};

			float attributeColorB[4];
		};

		union {
			struct {
				Color colorC;
			};

			float attributeColorC[4];
		};

		union {
			struct {
				Vector pointA;
				Vector pointB;
			};

			float attributePointAB[4];
		};

		union {
			struct {
				Vector pointC;
			};

			float attributePointC[2];
		};
	};
}