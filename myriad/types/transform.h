#pragma once

#include "vector.h"

namespace myr
{
	class Transform final
	{
	public:
		Transform();

		Transform identity();

		Transform scale(const float scaleUniform);
		Transform scale(const float scaleX, const float scaleY);

		Transform translate(const Vector v);
		Transform translate(const float x, const float y);

		Transform rotate(const float radians);

		const float *getRow0() const;
		const float *getRow1() const;

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