#pragma once

#include <cmath> // TODO: Debug?
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
			const Vector origin,
			const Transform transform)
			:atlasPosition(atlasPosition),
			atlasSize(atlasSize),
			position(transform.getRow0()[2], transform.getRow1()[2]),
			origin(origin)
		{
			row0[0] = transform.getRow0()[0];
			row0[1] = transform.getRow0()[1];
			row1[0] = transform.getRow1()[0];
			row1[1] = transform.getRow1()[1];
		}

		SpriteAttributes(
			const Vector atlasPosition,
			const Vector atlasSize,
			const Vector position,
			const Vector size,
			const Vector origin)
			:atlasPosition(atlasPosition),
			atlasSize(atlasSize),
			position(position),
			origin(origin)
		{
			row0[0] = size.x;
			row0[1] = 0;
			row1[0] = 0;
			row1[1] = size.y;
		}

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
			const float s = sin(angle);
			const float c = cos(angle);

			row0[0] = size.x * c;
			row0[1] = size.x * s;
			row1[0] = size.y * -s;
			row1[1] = size.y * c;
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