#pragma once

#include "types/vector.h"
#include "types/color.h"

namespace myr
{
	class Triangles
	{
	protected:
		static void drawTriangle(
			const myr::Vector &pointA,
			const myr::Vector &pointB,
			const myr::Vector &pointC,
			const myr::Color &colorA,
			const myr::Color &colorB,
			const myr::Color &colorC);

		static void drawTriangle(
			const myr::Vector &pointA,
			const myr::Vector &pointB,
			const myr::Vector &pointC,
			const myr::Color &color);
	};
}