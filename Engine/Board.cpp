#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(const Vei2& pos, Color c) const
{
	const int off_x = Sloc.x + BorderWidth + BorderPad;
	const int off_y = Sloc.y + BorderWidth + BorderPad;

	gfx.DrawRectDim(pos.x * CellDimension + off_x + BlockPad, pos.y * CellDimension + off_y + BlockPad,
		CellDimension - BlockPad * 2, CellDimension - BlockPad * 2, c);
}

void Board::DrawBlock()
{
}

void Board::DrawBorder() const
{
	const int left = Sloc.x;
	const int top = 0;
	const int right = Sloc.x + (BorderWidth + BorderPad) * 2 + Width * CellDimension + CellDimension;
	const int bottom = gfx.ScreenHeight;

	gfx.DrawRect(left, top, left + BorderWidth, bottom - BorderWidth, BorderColor);
	//left wall
	gfx.DrawRect(right - BorderWidth, top, right, bottom - BorderWidth, BorderColor);
	//right wall
}

int Board::GetGridWidth() const
{
	return Width;
}

int Board::GetGridHeight() const
{
	return Height;
}

int Board::GetCellDimension() const
{
	return CellDimension;
}

Vei2 Board::GetSloc() const
{
	return Sloc;
}
