#pragma once

#include "opengl/opengl.h"

namespace myr
{
	struct SharedUniforms
	{
		float width;
		float row0[3];

		float height;
		float row1[3];
	};
}