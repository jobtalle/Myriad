#pragma once

#include "../renderTarget/systems/sprites/spriteAttributes.h"
#include "types/vector.h"
#include "types/transform.h"

namespace myr
{
	class QuadRenderer
	{
	public:
		virtual void draw(
			const Transform &transform) = 0;
		virtual void draw(
			const Transform &transform,
			const Vector &scale) = 0;
		virtual void draw(
			const int x,
			const int y) = 0;
		virtual void draw(
			const int x,
			const int y,
			const Vector &scale) = 0;
		virtual void draw(
			const int x,
			const int y,
			const Vector &scale,
			const float angle) = 0;
	};
}