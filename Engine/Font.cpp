#include "Font.h"



Font::Font(const std::string& filename)
	:
	surface(filename),
	CharWidth(surface.GetWidth() / nCollums),
	CharHeight(surface.GetHeight() / nRows)
{
	assert(CharWidth * nCollums == surface.GetWidth());
	assert(CharHeight * nRows == surface.GetHeight());
}

void Font::DrawTexts(const std::string& text, const Vei2& pos, Graphics& gfx, Color s) const
{
	auto curpos = pos;
	SpriteEffect::Substitute E{Colors::White, s };
	for (auto c : text)
	{
		if (c == '\n')
		{
			curpos.x = pos.x;
			curpos.y += CharHeight;
			continue;
		}
		else if (c >= firstchar + 1 && c <= lastchar)
		{
			gfx.DrawSprite(curpos, MapCharRect(c), surface, E);
		}
		curpos.x += CharWidth;
	}

}

int Font::GetNumberOfLines(const std::string& text)
{
	for (auto c : text)
	{
		if (c == '\n')
		{
			NumberOfLines += 1;
		}
		
	}
	return NumberOfLines;
}

int Font::GetcharWidth() const
{
	return CharWidth;
}

int Font::GetcharHeight() const
{
	return CharHeight;
}

RectI Font::MapCharRect(char c) const
{
	assert(c >= firstchar && c <= lastchar);

	const int CharIndex = c - firstchar;
	const int yChar = CharIndex / nCollums;
	const int xChar = CharIndex % nCollums;

	return RectI(Vei2{ xChar * CharWidth, yChar * CharHeight }, CharWidth, CharHeight);
}
