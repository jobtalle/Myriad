#pragma once

#include "types/vector.h"
#include "types/color.h"

namespace myr
{
	class Lines
	{
	protected:
		static void drawLine(
			const myr::Vector &start,
			const myr::Vector &end,
			const myr::Color &color);

		static void drawLine(
			const myr::Vector &start,
			const myr::Vector &end,
			const myr::Color &colorStart,
			const myr::Color &colorEnd);

		static void drawRectangle(
			const myr::Vector &start,
			const myr::Vector &end,
			const myr::Color &color);
	};
}