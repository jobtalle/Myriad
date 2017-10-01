#include <cmath>

#include "vector.h"

myr::Vector::Vector()
	:x(0), y(0) {}

myr::Vector::Vector(const Vector &other)
	:x(other.x), y(other.y) {}

myr::Vector::Vector(const float both)
	:x(both), y(both) {}

myr::Vector::Vector(const float x, const float y)
	:x(x), y(y) {}

myr::Vector::Vector(const int both)
	:x(float(both)), y(float(both)) {}

myr::Vector::Vector(const int x, const int y)
	:x(float(x)), y(float(y)) {}

myr::Vector::Vector(const unsigned int both)
	:x(float(both)), y(float(both)) {}

myr::Vector::Vector(const unsigned int x, const unsigned int y)
:x(float(x)), y(float(y)) {}

float myr::Vector::dot(const Vector &other)
{
	return x * other.x + y * other.y;
}

float myr::Vector::length()
{
	return sqrt(dot(*this));
}

myr::Vector myr::Vector::normalized()
{
	const float scale = 1.0f / length();

	return Vector(*this) * scale;
}

myr::Vector &myr::Vector::normalize()
{
	const float scale = 1.0f / length();

	x *= scale;
	y *= scale;

	return *this;
}

myr::Vector &myr::Vector::operator+=(const Vector &vector)
{
	x += vector.x;
	y += vector.y;

	return *this;
}

myr::Vector &myr::Vector::operator-=(const Vector &vector)
{
	x -= vector.x;
	y -= vector.y;

	return *this;
}

myr::Vector &myr::Vector::operator*=(const Vector &vector)
{
	x *= vector.x;
	y *= vector.y;

	return *this;
}

myr::Vector &myr::Vector::operator/=(const Vector &vector)
{
	x /= vector.x;
	y /= vector.y;

	return *this;
}

myr::Vector &myr::Vector::operator*=(const float f)
{
	x *= f;
	y *= f;

	return *this;
}

myr::Vector &myr::Vector::operator/=(const float f)
{
	x /= f;
	y /= f;

	return *this;
}

myr::Vector myr::Vector::operator+(const Vector &vector) const
{
	return Vector(*this) += vector;
}

myr::Vector myr::Vector::operator-(const Vector &vector) const
{
	return Vector(*this) -= vector;
}

myr::Vector myr::Vector::operator*(const Vector &vector) const
{
	return Vector(*this) *= vector;
}

myr::Vector myr::Vector::operator/(const Vector &vector) const
{
	return Vector(*this) /= vector;
}

myr::Vector myr::Vector::operator*(const float f) const
{
	return Vector(*this) *= f;
}

myr::Vector myr::Vector::operator/(const float f) const
{
	return Vector(*this) /= f;
}

myr::Vector myr::Vector::operator-() const
{
	return Vector(-this->x, -this->y);
}

bool myr::Vector::operator==(const Vector &vector) const
{
	return x == vector.x && y == vector.y;
}

bool myr::Vector::operator!=(const Vector &vector) const
{
	return !(*this == vector);
}