#pragma once
#include "Graphics.h"
#include "Rect.h"
#include <vector>
#include <algorithm>
#include "Colors.h"


class Board
{
public:
	enum class CellContent
	{
		Empty,
		Blue,
		Green,
		Red,
		Yellow
	};
public:
	Board(Graphics& gfx);
	void DrawCell(const Vei2& pos, Color c) const;
	void DrawBlocks();
	void GetBlocks(const class Blocks& b);
	void DrawBorder() const;	//vaatii alarajan
	int GetGridWidth() const;
	int GetGridHeight() const;
	int GetCellDimension() const;
	Vei2 GetSloc() const;
	CellContent GetCellContent(const Vei2& pos) const;
	bool IsInsideBoard(const Vei2& target) const;

	std::vector<CellContent> Content;
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