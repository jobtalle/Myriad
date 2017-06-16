#include "quad.h"

myr::Quad::Quad(const Vector &origin)
	:Quad::Quad(Rect(0, 0), origin) {}

myr::Quad::Quad(const Rect &size, const Vector &origin)
	:size(size), origin(origin)
{
	calculateOriginFactor();
}

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

	calculateOriginFactor();
}

void myr::Quad::setSize(const Rect &size)
{
	this->size = size;

	calculateOriginFactor();
}

const myr::Vector &myr::Quad::getOriginFactor() const
{
	return originFactor;
}

void myr::Quad::calculateOriginFactor()
{
	originFactor = origin / size.toVector();
}