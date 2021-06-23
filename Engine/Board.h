#pragma once
#include "Graphics.h"
#include "Rect.h"
#include <vector>
#include <algorithm>
#include "Colors.h"
#include "Font.h"


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
	Board(Graphics& gfx, const Vei2& Sloc);
	void DrawCell(const Vei2& pos, Color c) const;
	void DrawBlocks() const;
	void DrawBorder() const;
	void DrawScore() const;
	int GetGridWidth() const;
	int GetGridHeight() const;
	int GetCellDimension() const;
	Vei2 GetSloc() const;
	CellContent GetCellContent(const Vei2& pos) const;
	CellContent SetCellContent(const Vei2& pos, CellContent ContentType);
	bool IsInsideBoard(const Vei2& target) const;
	void FullLine();
	bool FailCondition() const;
	void ResetBoard();
	
private:
	Graphics& gfx;
	Vei2 Sloc;
	int CellDimension = 20;
	int Width = 10;
	int Height = 28;
	int TotalGridCells = Width * Height;
	std::vector<CellContent> Content = { TotalGridCells, CellContent::Empty };
	int BorderWidth = 5;
	int BorderPad = 1;
	int BlockPad = 1;
	Color BorderColor = Colors::Gray;
	Font Score = { "kuvat//Consolas13x24.bmp" };
	int score = 0;
	int lines = 0;
	bool gameover = false;
};