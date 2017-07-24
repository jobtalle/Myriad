#pragma once

#include "primitives/lines/lines.h"
#include "primitives/points/points.h"
#include "primitives/triangles/triangles.h"

namespace myr
{
	class Primitives final : public Lines, public Points, public Triangles
	{
	public:
		using Lines::drawLine;
		using Lines::drawRectangle;

		using Points::drawPoint;

		using Triangles::fillTriangle;
		using Triangles::fillRectangle;
	};
}