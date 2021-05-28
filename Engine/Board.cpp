#include "Board.h"
#include "Blocks.h"

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

void Board::DrawBlocks()
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			switch (GetCellContent({x, y}))
			{
			case CellContent::Empty:
				break;
			case CellContent::Blue:
				DrawCell({ x,y }, Colors::Blue);
				break;
			case CellContent::Green:
				DrawCell({ x,y }, Colors::Green);
				break;
			case CellContent::Red:
				DrawCell({ x,y }, Colors::Red);
				break;
			}
		}
	}
}

void Board::GetBlocks(const Blocks& b)
{
	if (b.CollisionDown(*this))
	{

	}
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

Board::CellContent Board::GetCellContent(const Vei2& pos) const
{
	return Content[static_cast<std::vector<Board::CellContent, std::allocator<Board::CellContent>>::size_type>(pos.y) * Width + pos.x];
}

bool Board::IsInsideBoard(const Vei2& target) const
{
	return target.x >= 0 && target.x <= GetGridWidth() &&
		target.y >= 0 && target.y <= GetGridHeight();
}
