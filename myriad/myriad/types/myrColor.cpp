#include <algorithm>

#include "myrColor.h"

myr::Color::Color(const float r, const float g, const float b)
:r(r), g(g), b(b)
{

}

myr::Color myr::Color::operator+(const Color &c)
{
	return Color(
		fminf(getRed() + c.getRed(), 1),
		fminf(getGreen() + c.getGreen(), 1),
		fminf(getBlue() + c.getBlue(), 1));
}

myr::Color myr::Color::operator-(const Color &c)
{
	return Color(
		fmaxf(getRed() - c.getRed(), 0),
		fmaxf(getGreen() - c.getGreen(), 0),
		fmaxf(getBlue() - c.getBlue(), 0));
}

myr::Color myr::Color::operator*(const float f)
{
	return Color(
		fminf(fmaxf(getRed() * f, 0), 1),
		fminf(fmaxf(getGreen() * f, 0), 1),
		fminf(fmaxf(getBlue() * f, 0), 1));
}

float myr::Color::getRed() const
{
	return r;
}

float myr::Color::getGreen() const
{
	return g;
}

float myr::Color::getBlue() const
{
	return b;
}

float *myr::Color::getArray()
{
	return v;
}