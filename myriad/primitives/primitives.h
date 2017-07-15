#pragma once

#include "primitives/lines/lines.h"
#include "primitives/points/points.h"

namespace myr
{
	class Primitives final : public Lines, public Points
	{
	public:
		using Lines::drawLine;
		using Lines::drawRectangle;

		using Points::drawPoint;
	};
}