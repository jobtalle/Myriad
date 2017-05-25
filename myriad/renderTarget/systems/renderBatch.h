#pragma once

#include "renderSystems.h"

namespace myr
{
	class RenderBatch final
	{
	public:
		RenderBatch(const enum RenderSystems type, const unsigned int start);

		unsigned int getStart() const;
		unsigned int getEnd() const;
		enum RenderSystems getType() const;

	private:
		unsigned int start;
		unsigned int end;
		enum RenderSystems type;
	};
}