#include <cmath>

#include "vector.h"

myr::Vector::Vector()
	:x(0), y(0) {}

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

	return Vector(
		x * scale,
		y * scale);
}

myr::Vector &myr::Vector::normalize()
{
	const float scale = 1.0f / length();

	x *= scale;
	y *= scale;

	return *this;
}

myr::Vector myr::Vector::operator+(const Vector &other)
{
	return Vector(
		x + other.x,
		y + other.y);
}

myr::Vector myr::Vector::operator-(const Vector &other)
{
	return Vector(
		x - other.x,
		y - other.y);
}

myr::Vector myr::Vector::operator*(const Vector &other)
{
	return Vector(
		x * other.x,
		y * other.y);
}

myr::Vector myr::Vector::operator*(const float factor)
{
	return Vector(
		x * factor,
		y * factor);
}

myr::Vector myr::Vector::operator/(const Vector &other)
{
	return Vector(
		x / other.x,
		y / other.y);
}

myr::Vector myr::Vector::operator/(const float factor)
{
	return Vector(
		x / factor,
		y / factor);
}