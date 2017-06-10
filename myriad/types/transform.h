#pragma once

#include "vector.h"

namespace myr
{
	class Transform final
	{
		friend struct SpriteAttributes;
		friend class Renderer;

	public:
		Transform();

		Transform &identity();

		Transform &scale(const float scaleUniform);
		Transform &scale(const float scaleX, const float scaleY);

		Transform &translate(const Vector &v);
		Transform &translate(const float x, const float y);

		Transform &rotate(const float radians);

	private:
		union {
			float values[2][3];

			struct {
				float row0[2];
				float translateX;
				
				float row1[2];
				float translateY;
			};
		};
	};
}