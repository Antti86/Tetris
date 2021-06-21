#pragma once
#include <string>
#include "Graphics.h"
#include "Surface.h"
#include "Vec2.h"
#include "SpriteEffect.h"
#include <cassert>


class Font
{
public:
	Font(const std::string& filename);
	void DrawTexts(const std::string& text, const Vei2& pos, Graphics& gfx, Color s) const;
	int GetNumberOfLines(const std::string& text);
	int GetcharWidth() const;
	int GetcharHeight() const;
private:
	RectI MapCharRect(char c) const;
private:
	Surface surface;
	int CharWidth;
	int CharHeight;
	int NumberOfLines = 0;
	static constexpr int nCollums = 32;
	static constexpr int nRows = 3;
	static constexpr char firstchar = ' ';
	static constexpr char lastchar = '~';

};