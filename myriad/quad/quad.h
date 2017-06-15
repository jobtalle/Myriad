#pragma once

#include "../renderTarget/systems/sprites/spriteAttributes.h"
#include "types/vector.h"
#include "types/rect.h"
#include "types/transform.h"

namespace myr
{
	class Quad
	{
	public:
		Quad(const Vector &origin);
		Quad(const Rect &size, const Vector &origin);

		virtual void draw(
			const Transform &transform) const = 0;
		virtual void draw(
			const Transform &transform,
			const Vector &scale) const = 0;
		virtual void draw(
			const int x,
			const int y) const = 0;
		virtual void draw(
			const int x,
			const int y,
			const Vector &scale) const = 0;
		virtual void draw(
			const int x,
			const int y,
			const Vector &scale,
			const float angle) const = 0;

		Vector getOrigin() const;
		Rect getSize() const;
		void setOrigin(const Vector &origin);

	protected:
		Vector origin;
		Rect size;

		void setSize(const Rect &size);
	};
}