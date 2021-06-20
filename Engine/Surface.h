#pragma once
#include "Colors.h"
#include "ChiliWin.h"
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <cassert>
#include "Rect.h"

class Surface
{
public:
	Surface(const std::string& filename);
	Surface(int width, int height);
	Surface(const Surface&) = default;
	Surface(Surface&& donor) noexcept;
	Surface() = default;
	Surface& operator =(Surface&& rhs) noexcept;
	Surface& operator =(const Surface&) = default;
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	const Color* Data();
	void Fill(Color c);
	RectI GetRect() const;
	int GetWidth() const;
	int GetHeight() const;
private:
	int width = 0;
	int height = 0;
	std::vector<Color> Pixels;
};