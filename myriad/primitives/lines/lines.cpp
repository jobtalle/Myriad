#include "lines.h"
#include "renderTarget/renderTarget.h"
#include "renderTarget/systems/lines/lineAttributes.h"

void myr::Lines::drawLine(
	const myr::Vector &start,
	const myr::Vector &end,
	const myr::Color &colorStart,
	const myr::Color &colorEnd)
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_LINES, &LineAttributes(
		start,
		colorStart));
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_LINES, &LineAttributes(
		end,
		colorEnd));
}

void myr::Lines::drawLine(
	const myr::Vector &start,
	const myr::Vector &end,
	const myr::Color &color)
{
	Lines::drawLine(start, end, color, color);
}

void myr::Lines::drawRectangle(
	const myr::Vector &start,
	const myr::Vector &end,
	const myr::Color &colorLeftTop,
	const myr::Color &colorRightTop,
	const myr::Color &colorLeftBottom,
	const myr::Color &colorRightBottom)
{
	drawLine(start, Vector(end.x, start.y), colorLeftTop, colorRightTop);
	drawLine(start, Vector(start.x, end.y), colorLeftTop, colorLeftBottom);
	drawLine(end, Vector(end.x, start.y), colorRightBottom, colorRightTop);
	drawLine(end, Vector(start.x, end.y), colorRightBottom, colorLeftBottom);
}

void myr::Lines::drawRectangle(
	const myr::Vector &start,
	const myr::Vector &end,
	const myr::Color &color)
{
	Lines::drawRectangle(start, end, color, color, color, color);
}