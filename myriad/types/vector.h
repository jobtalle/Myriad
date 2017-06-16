#pragma once

namespace myr
{
	class Vector final
	{
	public:
		float x;
		float y;

		Vector(const float both);
		Vector(const float x, const float y);
		Vector(const int both);
		Vector(const int x, const int y);
		Vector(const unsigned int both);
		Vector(const unsigned int x, const unsigned int y);

		float dot(const Vector &other);
		float length();
		Vector normalized();
		Vector &normalize();

		Vector operator+(const Vector &other);
		Vector operator-(const Vector &other);
		Vector operator*(const Vector &other);
		Vector operator*(const float factor);
		Vector operator/(const Vector &other);
		Vector operator/(const float factor);
	};
}