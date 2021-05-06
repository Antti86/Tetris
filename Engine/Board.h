#pragma once
#include "Graphics.h"
#include "Rect.h"
#include <vector>
#include <algorithm>
#include "Colors.h"


class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Vei2& pos, Color c) const;
	void DrawBlock();
	void DrawBorder() const;
	int GetGridWidth() const;
	int GetGridHeight() const;


private:
	Graphics& gfx;
	Vei2 Sloc = { 180, 20 };
	int CellDimension = 20;
	int Width = 20;
	int Height = 26;
	int BorderWidth = 5;
	int BorderPad = 1;
	int BlockPad = 1;
	Color BorderColor = Colors::Gray;

};