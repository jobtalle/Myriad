#include <algorithm>

#include "color.h"

myr::Color::Color(const Color &color)
	:Color(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha()) {}

myr::Color::Color(const float r, const float g, const float b)
	:Color(r, g, b, 1) {}

myr::Color::Color(const float r, const float g, const float b, const float a)
	:r(r), g(g), b(b), a(a) {}

myr::Color &myr::Color::operator+=(const myr::Color &color)
{
	r = fminf(r + color.getRed(), 1);
	g = fminf(g + color.getGreen(), 1);
	b = fminf(b + color.getBlue(), 1);

	return *this;
}

myr::Color &myr::Color::operator-=(const myr::Color &color)
{
	r = fmaxf(getRed() - color.getRed(), 0);
	g = fmaxf(getGreen() - color.getGreen(), 0);
	b = fmaxf(getBlue() - color.getBlue(), 0);

	return *this;
}

myr::Color &myr::Color::operator*=(const myr::Color &color)
{
	r = fminf(fmaxf(getRed() * color.getRed(), 0), 1);
	g = fminf(fmaxf(getGreen() * color.getGreen(), 0), 1);
	b = fminf(fmaxf(getBlue() * color.getBlue(), 0), 1);
	a = fminf(fmaxf(getAlpha() * color.getAlpha(), 0), 1);
	
	return *this;
}

myr::Color &myr::Color::operator*=(const float f)
{
	r = fminf(fmaxf(getRed() * f, 0), 1);
	g = fminf(fmaxf(getGreen() * f, 0), 1);
	b = fminf(fmaxf(getBlue() * f, 0), 1);

	return *this;
}

myr::Color myr::Color::operator+(const Color &color) const
{
	return Color(*this) += color;
}

myr::Color myr::Color::operator-(const Color &color) const
{
	return Color(*this) -= color;
}

myr::Color myr::Color::operator*(const Color &color) const
{
	return Color(*this) *= color;
}

myr::Color myr::Color::operator*(const float f) const
{
	return Color(*this) *= f;
}

bool myr::Color::operator==(const Color &color) const
{
	return
		getRed() == color.getRed() &&
		getGreen() == color.getGreen() &&
		getBlue() == color.getBlue() &&
		getAlpha() == color.getAlpha();
}

bool myr::Color::operator!=(const Color &color) const
{
	return !(*this == color);
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

float myr::Color::getAlpha() const
{
	return a;
}

float *myr::Color::getArray()
{
	return v;
}