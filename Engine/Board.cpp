#include "Board.h"
#include "Blocks.h"

Board::Board(Graphics& gfx, const Vei2& Sloc)
	:
	gfx(gfx),
	Sloc(Sloc)
{
}

void Board::DrawCell(const Vei2& pos, Color c) const
{
	const int off_x = Sloc.x + BorderWidth + BorderPad;
	const int off_y = Sloc.y + BorderWidth + BorderPad;

	gfx.DrawRectDim(pos.x * CellDimension + off_x + BlockPad, pos.y * CellDimension + off_y + BlockPad,
		CellDimension - BlockPad * 2, CellDimension - BlockPad * 2, c);
}

void Board::DrawBlocks() const
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
			case CellContent::Yellow:
				DrawCell({ x,y }, Colors::Yellow);
				break;
			}
		}
	}
}




void Board::DrawBorder() const
{
	const int left = Sloc.x;
	const int top = 0;
	const int right = Sloc.x + (BorderWidth + BorderPad) * 2 + Width * CellDimension; //+ CellDimension;
	const int bottom = Sloc.y + (BorderWidth + BorderPad) * 2 + Height * CellDimension;

	gfx.DrawRect(left, top, left + BorderWidth, bottom - BorderWidth, BorderColor);
	//left wall
	gfx.DrawRect(right - BorderWidth, top, right, bottom - BorderWidth, BorderColor);
	//right wall
	gfx.DrawRect(left, bottom, right, bottom - BorderWidth, BorderColor);
}

void Board::DrawScore() const
{
	std::string ScoreCount = std::to_string(score);
	Vei2 loc(GetSloc().x - 100, GetSloc().y);
	Score.DrawTexts(ScoreCount, loc, gfx, Colors::White);
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

Board::CellContent Board::SetCellContent(const Vei2& pos, CellContent ContentType)
{
	return Content[static_cast<std::vector<Board::CellContent, std::allocator<Board::CellContent>>::size_type>(pos.y) * Width + pos.x] = ContentType;
}

bool Board::IsInsideBoard(const Vei2& target) const
{
	return target.x >= 0 && target.x <= GetGridWidth() - 1 &&
		target.y >= 0 && target.y <= GetGridHeight() - 1;
}

void Board::FullLine()
{
	int linecount = 0;
	for (int y = 1; y < Height; ++y)
	{
		
		std::vector<CellContent>::iterator itB = Content.begin() + y * Width;
		std::vector<CellContent>::iterator itE = Content.begin() + y * Width + Width;

		if(std::all_of(itB, itE, [&](CellContent& c) {return c != CellContent::Empty; }))
		{
			std::transform(itB, itE, itB, [&](CellContent& c) { return c = CellContent::Empty; });
			std::rotate(Content.begin(), itE - Width, itE);
			linecount += 1;
			score += 100;
			if (linecount == 4)
			{
				score += 400;
			}
		}
	}
}
