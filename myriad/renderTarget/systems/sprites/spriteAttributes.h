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
			const float angle,
			const float z)
			:atlasPosition(atlasPosition),
			atlasSize(atlasSize),
			position(position),
			size(size) {}

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
	};
}