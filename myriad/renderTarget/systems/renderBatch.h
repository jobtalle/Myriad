#pragma once

#include "renderSystems.h"

namespace myr
{
	class RenderBatch final
	{
	public:
		RenderBatch(const enum RenderSystems type, const size_t start);

		size_t getStart() const;
		size_t getEnd() const;
		enum RenderSystems getType() const;
		void increment();

	private:
		size_t start;
		size_t end;
		enum RenderSystems type;
	};
}