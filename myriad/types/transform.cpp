#include <cmath> // TODO: Redundant when lookup table exists

#include "transform.h"

myr::Transform::Transform()
{
	identity();
}

myr::Transform myr::Transform::identity()
{
	values[0][0] = 1;
	values[0][1] = 0;
	values[0][2] = 0;

	values[1][0] = 0;
	values[1][1] = 1;
	values[1][2] = 0;

	return *this;
}

myr::Transform myr::Transform::scale(const float scaleUniform)
{
	return scale(scaleUniform, scaleUniform);
}

myr::Transform myr::Transform::scale(const float scaleX, const float scaleY)
{
	row0[0] *= scaleX;
	row0[1] *= scaleX;
	row1[0] *= scaleY;
	row1[1] *= scaleY;

	return *this;
}

myr::Transform myr::Transform::translate(const Vector v)
{
	translateX += v.x;
	translateY += v.y;

	return *this;
}

myr::Transform myr::Transform::translate(const float x, const float y)
{
	translateX += x;
	translateY += y;

	return *this;
}

myr::Transform myr::Transform::rotate(const float radians)
{
	// Todo: Use LUT

	const float c = cos(radians);
	const float s = sin(radians);

	const float original[2][2] = {row0[0], row1[0], row0[1], row1[1]};

	row0[0] = original[0][0] * c + original[0][1] * s;
	row0[1] = original[0][0] * -s + original[0][1] * c;
	row1[0] = original[1][0] * c + original[1][1] * s;
	row1[1] = original[1][0] * -s + original[1][1] * c;

	return *this;
}

const float *myr::Transform::getRow0() const
{
	return values[0];
}

const float *myr::Transform::getRow1() const
{
	return values[1];
}