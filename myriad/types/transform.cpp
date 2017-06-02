#include "transform.h"

myr::Transform::Transform()
{
	identity();
}

void myr::Transform::identity()
{
	values[0][0] = 1;
	values[0][1] = 0;
	values[0][2] = 0;

	values[1][0] = 0;
	values[1][1] = 1;
	values[1][2] = 0;
}

void myr::Transform::translate(const Vector v)
{
	translateX += v.x;
	translateY += v.y;
}

void myr::Transform::translate(const float x, const float y)
{
	translateX += x;
	translateY += y;
}