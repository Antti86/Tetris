#include "Surface.h"

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	Pixels(width * height)
{
}

void Surface::PutPixels(int x, int y, Color c)
{
	Pixels[static_cast<std::vector<Color, std::allocator<Color>>::size_type>(y) * width + x] = c;
}

Color Surface::GetPixels(int x, int y) const
{
	return Pixels[static_cast<std::vector<Color, std::allocator<Color>>::size_type>(y) * width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}
