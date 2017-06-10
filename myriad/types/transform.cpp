#include <cmath> // TODO: Redundant when lookup table exists

#include "transform.h"

myr::Transform::Transform()
{
	identity();
}

myr::Transform::Transform(
	const float row00,
	const float row01,
	const float row02,
	const float row10,
	const float row11,
	const float row12)
{
	values[0][0] = row00;
	values[0][1] = row01;
	values[0][2] = row02;
	
	values[1][0] = row10;
	values[1][1] = row11;
	values[1][2] = row12;
}

myr::Transform &myr::Transform::identity()
{
	values[0][0] = 1;
	values[0][1] = 0;
	values[0][2] = 0;

	values[1][0] = 0;
	values[1][1] = 1;
	values[1][2] = 0;

	return *this;
}

myr::Transform &myr::Transform::scale(const float scaleUniform)
{
	return scale(scaleUniform, scaleUniform);
}

myr::Transform &myr::Transform::scale(const float scaleX, const float scaleY)
{
	row0[0] *= scaleX;
	row0[1] *= scaleX;
	row1[0] *= scaleY;
	row1[1] *= scaleY;

	return *this;
}

myr::Transform &myr::Transform::translate(const Vector &v)
{
	return translate(v.x, v.y);
}

myr::Transform &myr::Transform::translate(const float x, const float y)
{
	translateX += row0[0] * x + row0[1] * y;
	translateY += row1[0] * x + row1[1] * y;

	return *this;
}

myr::Transform &myr::Transform::rotate(const float radians)
{
	// Todo: Use LUT

	const float c = cos(radians);
	const float s = sin(radians);

	const float original[2][2] = {row0[0], row1[0], row0[1], row1[1]};

	row0[0] = original[0][0] * c - original[0][1] * s;
	row0[1] = original[0][0] * s + original[0][1] * c;
	row1[0] = original[1][0] * c - original[1][1] * s;
	row1[1] = original[1][0] * s + original[1][1] * c;

	return *this;
}

myr::Transform myr::Transform::operator*(const Transform &other) const
{
	return Transform(
		values[0][0] * other.values[0][0] + values[0][1] * other.values[1][0],
		values[0][0] * other.values[0][1] + values[0][1] * other.values[1][1],
		values[0][0] * other.values[0][2] + values[0][1] * other.values[1][2] + values[0][2],
		values[1][0] * other.values[0][0] + values[1][1] * other.values[1][0],
		values[1][0] * other.values[0][1] + values[1][1] * other.values[1][1],
		values[1][0] * other.values[0][2] + values[1][1] * other.values[1][2] + values[1][2]);
}

myr::Vector myr::Transform::operator*(const Vector &vector) const
{
	return Vector(
		row0[0] * vector.x + row0[1] * vector.y + translateX,
		row1[0] * vector.x + row1[1] * vector.y + translateY);
}