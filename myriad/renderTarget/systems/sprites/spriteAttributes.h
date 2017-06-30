#pragma once

#include <cmath> // TODO: Redundant if LUT is used
#include <cstdint>

#include "types/vector.h"
#include "types/transform.h"
#include "renderer/atlas.h"

namespace myr
{
	struct SpriteAttributes
	{
		SpriteAttributes(
			const myr::Atlas::Location &location,
			const Vector &size,
			const Vector &origin,
			const Transform &transform)
			:atlasPosition(location.location),
			atlasSize(location.size),
			position(transform.row0[2], transform.row1[2]),
			origin(origin)
		{
			row0[0] = transform.row0[0] * size.x;
			row0[1] = transform.row0[1] * size.x;
			row1[0] = transform.row1[0] * size.y;
			row1[1] = transform.row1[1] * size.y;
		}

		SpriteAttributes(
			const myr::Atlas::Location &location,
			const Vector &position,
			const Vector &size,
			const Vector &origin)
			:atlasPosition(location.location),
			atlasSize(location.size),
			position(position),
			origin(origin)
		{
			row0[0] = size.x;
			row0[1] = 0;
			row1[0] = 0;
			row1[1] = size.y;
		}

		SpriteAttributes(
			const myr::Atlas::Location &location,
			const Vector &position,
			const Vector &size,
			const Vector &origin,
			const float angle)
			:atlasPosition(location.location),
			atlasSize(location.size),
			position(position),
			origin(origin)
		{
			// Todo: Use LUT

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