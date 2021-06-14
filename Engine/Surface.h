#pragma once
#include "Colors.h"
#include <vector>

class Surface
{
public:
	Surface(int width, int height);
	void PutPixels(int x, int y, Color c);
	Color GetPixels(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
private:
	std::vector<Color> Pixels;
	int width;
	int height;
};