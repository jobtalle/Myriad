#include "lines.h"
#include "renderTarget/renderTarget.h"
#include "renderTarget/systems/lines/lineAttributes.h"

void myr::Lines::drawLine(
	const myr::Vector &start,
	const myr::Vector &end,
	const myr::Color &color)
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_LINES, &LineAttributes(
		start,
		end,
		color,
		color));
}

void myr::Lines::drawLine(
	const myr::Vector &start,
	const myr::Vector &end,
	const myr::Color &colorStart,
	const myr::Color &colorEnd)
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_LINES, &LineAttributes(
		start,
		end,
		colorStart,
		colorEnd));
}