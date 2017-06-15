#include "rect.h"

myr::Rect::Rect(const uint16_t width, const uint16_t height)
	:width(width), height(height)
{
	
}

uint16_t myr::Rect::getWidth() const
{
	return width;
}

uint16_t myr::Rect::getHeight() const
{
	return height;
}

myr::Vector myr::Rect::toVector() const
{
	return Vector(width, height);
}

void myr::Rect::setWidth(const uint16_t width)
{
	this->width = width;
}

void myr::Rect::setHeight(const uint16_t height)
{
	this->height = height;
}