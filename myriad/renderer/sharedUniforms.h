#pragma once

#include "opengl/opengl.h"

namespace myr
{
	struct SharedUniforms
	{
		struct
		{
			GLfloat width;
			GLfloat height;
		} target;
	};
}