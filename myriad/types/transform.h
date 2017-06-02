#pragma once

#include "vector.h"

namespace myr
{
	class Transform final
	{
	public:
		Transform();
		void identity();
		void translate(const Vector v);
		void translate(const float x, const float y);

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