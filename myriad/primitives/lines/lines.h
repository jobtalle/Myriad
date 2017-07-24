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
			const myr::Color &colorStart,
			const myr::Color &colorEnd);

		static void drawLine(
			const myr::Vector &start,
			const myr::Vector &end,
			const myr::Color &color);

		static void drawRectangle(
			const myr::Vector &start,
			const myr::Vector &end,
			const myr::Color &colorLeftTop,
			const myr::Color &colorRightTop,
			const myr::Color &colorLeftBottom,
			const myr::Color &colorRightBottom);

		static void drawRectangle(
			const myr::Vector &start,
			const myr::Vector &end,
			const myr::Color &color);
	};
}