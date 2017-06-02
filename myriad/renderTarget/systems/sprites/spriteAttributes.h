#pragma once

#include <cstdint>

#include "types/vector.h"
#include "types/transform.h"

namespace myr
{
	struct SpriteAttributes
	{
		SpriteAttributes(
			const Vector atlasPosition,
			const Vector atlasSize,
			const Vector position,
			const Vector size,
			const Vector origin,
			const float angle)
			:atlasPosition(atlasPosition),
			atlasSize(atlasSize),
			position(position),
			origin(origin)
		{
			// TODO: Rotate here

			row0[0] = size.x;
			row0[1] = 0;
			row1[0] = 0;
			row1[1] = size.y;
		}

		union {
			struct {
				Vector atlasPosition;
				Vector atlasSize;
			};

			float attributeAtlas[4];
		};

		union {
			struct {
				float row0[2];
				float row1[2];
			};

			float attributeScaleRotate[4];
		};

		union {
			struct {
				Vector origin;
				Vector position;
			};

			float attributeTransform[4];
		};
	};
}