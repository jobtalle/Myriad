#include "renderBatch.h"

myr::RenderBatch::RenderBatch(const enum RenderSystems type, const size_t start)
	:type(type), start(start), end(start + 1) { }

size_t myr::RenderBatch::getStart() const
{
	return start;
}

size_t myr::RenderBatch::getEnd() const
{
	return end;
}

enum myr::RenderSystems myr::RenderBatch::getType() const
{
	return type;
}

void myr::RenderBatch::increment()
{
	++end;
}