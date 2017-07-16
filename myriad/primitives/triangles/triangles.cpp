#include "triangles.h"
#include "renderTarget/renderTarget.h"
#include "renderTarget/systems/triangles/triangleAttributes.h"

void myr::Triangles::drawTriangle(
	const myr::Vector &pointA,
	const myr::Vector &pointB,
	const myr::Vector &pointC,
	const myr::Color &colorA,
	const myr::Color &colorB,
	const myr::Color &colorC)
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_TRIANGLES, &TriangleAttributes(
		pointA,
		pointB,
		pointC,
		colorA,
		colorB,
		colorC));
}

void myr::Triangles::drawTriangle(
	const myr::Vector &pointA,
	const myr::Vector &pointB,
	const myr::Vector &pointC,
	const myr::Color &color)
{
	myr::Triangles::drawTriangle(pointA, pointB, pointC, color, color, color);
}