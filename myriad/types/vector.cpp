#include "vector.h"

myr::Vector::Vector(const float x = 0, const float y = 0)
	:x(x), y(y) {}

myr::Vector::Vector(const int x, const int y)
	:x(float(x)), y(float(y)) {}