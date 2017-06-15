#include "quad.h"

myr::Quad::Quad(const Vector &origin)
	:Quad::Quad(Rect(0, 0), origin) {}

myr::Quad::Quad(const Rect &size, const Vector &origin)
	:size(size), origin(origin) {}

myr::Vector myr::Quad::getOrigin() const
{
	return origin;
}

myr::Rect myr::Quad::getSize() const
{
	return size;
}

void myr::Quad::setOrigin(const Vector &origin)
{
	this->origin = origin;
}

void myr::Quad::setSize(const Rect &size)
{
	this->size = size;
}