#pragma once

#include <cstdint>

#include "types/myrVector.h"

namespace myr
{
	struct SpriteAttributes
	{
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
				float angle;
				float z;
			};

			float attributeLocation[4];
		};
	};
}