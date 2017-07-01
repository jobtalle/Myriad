#include "lines.h"
#include "renderTarget/renderTarget.h"
#include "renderTarget/systems/lines/lineAttributes.h"

void myr::Lines::drawLine(const myr::Vector &start, const myr::Vector &end)
{
	RenderTarget::getCurrent()->render(RENDER_SYSTEM_LINES, &LineAttributes(
		start,
		end,
		myr::Color(0, 0, 1)));
}