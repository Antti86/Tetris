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
			case CellContent::Cyan:
				DrawCell({ x,y }, Colors::Cyan);
				break;
			case CellContent::DarkGreen:
				DrawCell({ x,y }, Colors::DarkGreen);
				break;
			case CellContent::DarkRed:
				DrawCell({ x,y }, Colors::DarkRed);
				break;
			case CellContent::LawnGreen:
				DrawCell({ x,y }, Colors::LawnGreen);
				break;
			case CellContent::MidnightBlue:
				DrawCell({ x,y }, Colors::MidnightBlue);
				break;
			case CellContent::Orange:
				DrawCell({ x,y }, Colors::Orange);
				break;
			case CellContent::White:
				DrawCell({ x,y }, Colors::White);
				break;
			case CellContent::Scarlet:
				DrawCell({ x,y }, Colors::Scarlet);
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
	std::string LineCount = std::to_string(lines);
	Vei2 ScoreCountLoc(GetSloc().x - 100, GetSloc().y + 30);
	Vei2 ScoreTextLoc(GetSloc().x - 150, GetSloc().y);
	Vei2 LineCountloc(GetSloc().x - 100, GetSloc().y + 130);
	Vei2 LineTextloc(GetSloc().x - 150, GetSloc().y + 100);

	Score.DrawTexts(ScoreCount, ScoreCountLoc, gfx, Colors::White);
	Score.DrawTexts("Score", ScoreTextLoc, gfx, Colors::White);
	Score.DrawTexts(LineCount, LineCountloc, gfx, Colors::White);
	Score.DrawTexts("Lines", LineTextloc, gfx, Colors::White);
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
			lines += 1;
			LevelCheck();
			score += 100;
			if (linecount == 4)
			{
				score += 500;
			}
			else if (linecount == 3)
			{
				score += 100;
			}
			else if (linecount == 2)
			{
				score += 50;
			}
		}
	}
}

bool Board::FailCondition()
{
	bool gameover;
	for (int y = 1; y < 4; ++y)
	{
		std::vector<CellContent>::iterator itB = Content.begin() + y * Width;
		std::vector<CellContent>::iterator itE = Content.begin() + y * Width + Width;
		if (std::any_of(itB, itE, [&](CellContent& c) {return c != CellContent::Empty; }))
		{
			gameover = true;
		}
		else
		{
			gameover = false;
		}
	}
	return gameover;
}

void Board::ResetBoard()
{
	for (auto& s : Content)
	{
		s = CellContent::Empty;
	}
	score = 0;
	lines = 0;
	lvl = Levels::Level1;
}

int Board::GetLineNumber() const
{
	return lines;
}

int Board::GetScore() const
{
	return score;
}

void Board::LevelCheck()
{
	if (lines < 10)
	{
		lvl = Levels::Level1;
	}
	else if (lines > 10 && lines < 20)
	{
		lvl = Levels::Level2;
	}
	else if (lines > 20)
	{
		lvl = Levels::Level3;
	}
}

Board::Levels Board::GetLvl() const
{
	return lvl;
}




