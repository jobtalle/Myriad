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
		colorA,
		pointA));
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_TRIANGLES, &TriangleAttributes(
		colorB,
		pointB));
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_TRIANGLES, &TriangleAttributes(
		colorC,
		pointC));
}

void myr::Triangles::drawTriangle(
	const myr::Vector &pointA,
	const myr::Vector &pointB,
	const myr::Vector &pointC,
	const myr::Color &color)
{
	myr::Triangles::drawTriangle(pointA, pointB, pointC, color, color, color);
}