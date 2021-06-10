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
	void DrawBorder() const;	//vaatii alarajan
	int GetGridWidth() const;
	int GetGridHeight() const;
	int GetCellDimension() const;
	Vei2 GetSloc() const;
	CellContent GetCellContent(const Vei2& pos) const;
	CellContent SetCellContent(const Vei2& pos, CellContent ContentType);
	bool IsInsideBoard(const Vei2& target) const;
	void FullLine();
private:
	Graphics& gfx;
	Vei2 Sloc = { 280, 20 };
	int CellDimension = 20;
	int Width = 10;
	int Height = 28;
	int TotalGridCells = Width * Height;
	std::vector<CellContent> Content = { TotalGridCells, CellContent::Empty };
	int BorderWidth = 5;
	int BorderPad = 1;
	int BlockPad = 1;
	Color BorderColor = Colors::Gray;
	
};