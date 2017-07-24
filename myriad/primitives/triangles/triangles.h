#pragma once

#include "types/vector.h"
#include "types/color.h"

namespace myr
{
	class Triangles
	{
	protected:
		static void fillTriangle(
			const myr::Vector &pointA,
			const myr::Vector &pointB,
			const myr::Vector &pointC,
			const myr::Color &colorA,
			const myr::Color &colorB,
			const myr::Color &colorC);

		static void fillTriangle(
			const myr::Vector &pointA,
			const myr::Vector &pointB,
			const myr::Vector &pointC,
			const myr::Color &color);

		static void fillRectangle(
			const myr::Vector &start,
			const myr::Vector &end,
			const myr::Color &colorLeftTop,
			const myr::Color &colorRightTop,
			const myr::Color &colorLeftBottom,
			const myr::Color &colorRightBottom);

		static void fillRectangle(
			const myr::Vector &start,
			const myr::Vector &end,
			const myr::Color &color);
	};
}