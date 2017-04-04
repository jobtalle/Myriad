#include <myriad/myrSprite.h>

#include <cstring>

myr::Sprite::Sprite(const Rect size, const char *image)
:flags(0), size(size)
{
	pixels = new char(size.getWidth() * size.getHeight() * 4);

	std::memcpy(pixels, image, sizeof(pixels));
}