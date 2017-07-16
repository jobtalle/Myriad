#include "points.h"
#include "renderTarget/renderTarget.h"
#include "renderTarget/systems/points/pointAttributes.h"

void myr::Points::drawPoint(
	const myr::Vector &location,
	const myr::Color &color)
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_POINTS, &PointAttributes(
		location,
		color));
}