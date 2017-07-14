#pragma once

namespace myr
{
	class Vector final
	{
	public:
		float x;
		float y;

		Vector();
		Vector(const Vector &vector);
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

		Vector &operator+=(const Vector &vector);
		Vector &operator-=(const Vector &vector);
		Vector &operator*=(const Vector &vector);
		Vector &operator/=(const Vector &vector);
		Vector &operator*=(const float f);
		Vector &operator/=(const float f);

		Vector operator+(const Vector &vector) const;
		Vector operator-(const Vector &vector) const;
		Vector operator*(const Vector &vector) const;
		Vector operator/(const Vector &vector) const;
		Vector operator*(const float f) const;
		Vector operator/(const float f) const;

		bool operator==(const Vector &vector) const;
		bool operator!=(const Vector &vector) const;
	};
}