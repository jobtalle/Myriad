#pragma once

#include <cstdint>

#include "types/vector.h"

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
			size(size),
			origin(origin),
			angle(angle) {}

		union {
			struct {
				Vector atlasPosition;
				Vector atlasSize;
			};

			float attributeAtlas[4];
		};

		union {
			struct {
				Vector position;
				Vector size;
			};

			float attributeLocation[4];
		};

		union {
			struct {
				Vector origin;
				float angle;
			};

			float attributeTransform[3];
		};
	};
}