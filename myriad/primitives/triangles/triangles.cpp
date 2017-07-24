#include "triangles.h"
#include "renderTarget/renderTarget.h"
#include "renderTarget/systems/triangles/triangleAttributes.h"

void myr::Triangles::fillTriangle(
	const myr::Vector &pointA,
	const myr::Vector &pointB,
	const myr::Vector &pointC,
	const myr::Color &colorA,
	const myr::Color &colorB,
	const myr::Color &colorC)
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_TRIANGLES, &TriangleAttributes(
		colorA,
		pointA));
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_TRIANGLES, &TriangleAttributes(
		colorB,
		pointB));
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_TRIANGLES, &TriangleAttributes(
		colorC,
		pointC));
}

void myr::Triangles::fillTriangle(
	const myr::Vector &pointA,
	const myr::Vector &pointB,
	const myr::Vector &pointC,
	const myr::Color &color)
{
	myr::Triangles::fillTriangle(pointA, pointB, pointC, color, color, color);
}

void myr::Triangles::fillRectangle(
	const myr::Vector &start,
	const myr::Vector &end,
	const myr::Color &colorLeftTop,
	const myr::Color &colorRightTop,
	const myr::Color &colorLeftBottom,
	const myr::Color &colorRightBottom)
{
	myr::Triangles::fillTriangle(
		start,
		Vector(start.x, end.y),
		end,
		colorLeftTop,
		colorLeftBottom,
		colorRightBottom);
	myr::Triangles::fillTriangle(
		start,
		Vector(end.x, start.y),
		end,
		colorLeftTop,
		colorRightTop,
		colorRightBottom);
}

void myr::Triangles::fillRectangle(
	const myr::Vector &start,
	const myr::Vector &end,
	const myr::Color &color)
{
	myr::Triangles::fillRectangle(start, end, color, color, color, color);
}