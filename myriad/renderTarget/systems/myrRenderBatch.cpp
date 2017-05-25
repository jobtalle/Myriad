#include "myrRenderBatch.h"

myr::RenderBatch::RenderBatch(const enum RenderSystems type, const unsigned int start)
	:type(type), start(start), end(start) { }

unsigned int myr::RenderBatch::getStart() const
{
	return start;
}

unsigned int myr::RenderBatch::getEnd() const
{
	return end;
}

enum myr::RenderSystems myr::RenderBatch::getType() const
{
	return type;
}