#include <myriad/myrColor.h>

myr::Color::Color(const float r, const float g, const float b)
:r(r), g(g), b(b)
{

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