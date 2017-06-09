#pragma once

namespace myr
{
	class Vector final
	{
	public:
		float x;
		float y;

		Vector(const float x, const float y);
		Vector(const int x, const int y);
		Vector(const unsigned int x, const unsigned int y);
	};
}