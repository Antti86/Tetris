#include "Blocks.h"

Blocks::Blocks(Vei2 StartPos, const Board& brd)
	:
	StartPos(StartPos),
	rng(std::random_device() ())
{
	
	type = RandomType(rng);
	c = SetColor(brd);
	Vei2 loc = StartPos;

	MovingBlocks.reserve(Linerialtotal);			//Linerial Grid for easier rotation
	for (int i = 0; i < top; i++)					
	{												
		loc.x += 1;									
		MovingBlocks.emplace_back(loc, c);
	}
	for (int i = 0; i < right; i++)					// 0  1  2  3
	{												// 11 12 13 4
		loc.y += 1;									// 10 15 14 5
		MovingBlocks.emplace_back(loc, c);			// 9  8  7  6
	}
	for (int i = 0; i < bottom; i++)
	{
		loc.x -= 1;
		MovingBlocks.emplace_back(loc, c);
	}
	for (int i = 0; i < left; i++)
	{
		loc.y -= 1;
		MovingBlocks.emplace_back(loc, c);
		
	}
	loc.x += 1;
	MovingBlocks.emplace_back(loc, c);
	loc.x += 1;
	MovingBlocks.emplace_back(loc, c);
	loc.y += 1;
	MovingBlocks.emplace_back(loc, c);
	loc.x -= 1;
	MovingBlocks.emplace_back(loc, c);

	std::copy(MovingBlocks.begin(), MovingBlocks.end(), std::back_inserter(StartingPos));
	for (int i = 0; i < Linerialtotal; i++)
	{
		if (type == BlockType::I && (i == 1 || i == 15 || i == 8 || i == 12))						// 0  1  2  3
		{																							// 11 12 13 4
			MovingBlocks[i].Empty = false;															// 10 15 14 5
		}																							// 9  8  7  6
		if (type == BlockType::L && (i == 0 || i == 1 || i == 15 || i == 12))
		{
			MovingBlocks[i].Empty = false;
		}
		if (type == BlockType::Brick && (i == 12 || i == 13 || i == 14 || i == 15))
		{
			MovingBlocks[i].Empty = false;
		}
		if (type == BlockType::HalfCross && (i == 1 || i == 11 || i == 12 || i == 15))
		{
			MovingBlocks[i].Empty = false;
		}
		if (type == BlockType::N && (i == 2 || i == 12 || i == 15 || i == 13))
		{
			MovingBlocks[i].Empty = false;
		}
		if (type == BlockType::MirrorN && (i == 1 || i == 12 || i == 14 || i == 13))
		{
			MovingBlocks[i].Empty = false;
		}
		if (type == BlockType::MirrorL && (i == 3 || i == 2 || i == 13 || i == 14))
		{
			MovingBlocks[i].Empty = false;
		}
	}
}

Blocks& Blocks::operator=(const Blocks& b)
{
	type = b.type;
	ContentColor = b.ContentColor;
	for (int i = 0; i < MovingBlocks.size(); i++)
	{
		this->MovingBlocks[i].pos = this->StartingPos[i].pos;
		this->MovingBlocks[i].BColor = b.MovingBlocks[i].BColor;
		this->MovingBlocks[i].Empty = b.MovingBlocks[i].Empty;
	}
	return *this;
}

void Blocks::Draw(Board& brd) const
{
	for (auto& s : MovingBlocks)
	{
		if (!s.Empty && brd.IsInsideBoard(s.pos))
		{
			s.Draw(brd);
		}
	}
}

void Blocks::DrawOutsideBoard(Board& brd) const
{
	for (auto& s : MovingBlocks)
	{
		if (!s.Empty)
		{
			s.Draw(brd);
		}
	}
}

Vei2 Blocks::GetNextLoc(const Vei2& delta_loc, char m) const
{
	Vei2 l(MostSideBlock(m));
	l += delta_loc;
	return l;
}

bool Blocks::CollisionDown(const Board& brd) const
{
	Vei2 next = GetNextLoc(Vei2(0, 1), 'd');
	if ( next.y >= brd.GetGridHeight() || TestNextLoc(brd, Vei2(0, 1)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Blocks::TransferBlocksToBoard(Board& brd)
{
	for (int i = 0; i < MovingBlocks.size(); i++)
	{
		if (MovingBlocks[i].GetEmpty())
		{
			continue;
		}
		else
		{
			Vei2 pos = MovingBlocks[i].GetPos();
			brd.SetCellContent(pos, ContentColor);
		}
	}
}

void Blocks::SideMovement(Vei2& delta_loc, Keyboard& kbd, const Board& brd, float dt, GameSettings& g)
{
	if (kbd.KeyIsPressed(VK_LEFT) && brd.IsInsideBoard(MostSideBlock('l') += {-1, 0}) && !TestNextLoc(brd, Vei2(-1, 0)))
	{
		delta_loc = { -1, 0 };
	}
	else if (kbd.KeyIsPressed(VK_RIGHT) && brd.IsInsideBoard(MostSideBlock('r') += {1, 0}) && !TestNextLoc(brd, Vei2(1, 0)))
	{
		delta_loc = { 1, 0 };
	}
	else
	{
		delta_loc = { 0, 0 };
	}
	PositionFix(brd);
	MovementSpeedSide(delta_loc, dt, brd, g);
}

void Blocks::MoveBy(Vei2 delta_loc)
{
	for (auto& s : MovingBlocks)
	{
		s.Moveby(delta_loc);
	}
}

void Blocks::Movement(Vei2& delta_loc, Keyboard& kbd, const Board& brd, float dt, GameSettings& g)
{
	LevelCheck(brd);
	delta_loc = { 0, 1 };
	const Keyboard::Event e = kbd.ReadKey();
	SideMovement(delta_loc, kbd, brd, dt, g);
	if (kbd.KeyIsPressed(VK_DOWN))
	{
		BlockMoveCounterDown += dt + (BlockMoveRateDown * 0.06f);
	}
	if (e.IsPress() && e.GetCode() == VK_UP)
	{
		Rotate(brd);
	}
	
	PositionFix(brd);
	MovementSpeedDown(delta_loc, dt, brd);
}

void Blocks::MovementSpeedSide(Vei2& delta_loc, float dt, const Board& brd, GameSettings& g)
{
	BlockMoveRateSide = g.TranslateSpeed();
	BlockMoveCounterSide += dt;

	if (BlockMoveCounterSide >= BlockMoveRateSide && (delta_loc == Vei2( - 1, 0 ) || delta_loc == Vei2( 1, 0 )))
	{
		MoveBy(delta_loc);
		BlockMoveCounterSide = 0;
	}
}

void Blocks::MovementSpeedDown(Vei2& delta_loc, float dt, const Board& brd)
{
	BlockMoveCounterDown += dt;
	if (BlockMoveCounterDown >= BlockMoveRateDown)
	{
		MoveBy(Vei2(0, 1));
		BlockMoveCounterDown = 0;
	}
}

void Blocks::PositionFix(const Board& brd)
{
	if (!brd.IsInsideBoard(MostSideBlock('r')))
	{
		MoveBy(Vei2(-1, 0));
	}
	if (!brd.IsInsideBoard(MostSideBlock('l')))
	{
		MoveBy(Vei2(1, 0));
	}
}

void Blocks::Rotate(const Board& brd)
{
	std::vector<BlockSeg> temp;
	temp.reserve(MovingBlocks.size());
	std::rotate_copy(MovingBlocks.begin(), MovingBlocks.begin() + 3, MovingBlocks.end() - 4, std::back_inserter(temp));
	std::rotate_copy(MovingBlocks.begin() + 12, MovingBlocks.begin() + 13, MovingBlocks.end(), std::back_inserter(temp));
	if (std::all_of(temp.begin(), temp.end(),
		[&](BlockSeg& s)
		{
			return brd.GetCellContent(s.GetPos()) == Board::CellContent::Empty;
		}))
	{
		for (int i = 0; i < temp.size(); i++)											// 0  1  2  3
		{																				// 11 12 13 4
			MovingBlocks[i].pos = temp[i].pos;											// 10 15 14 5
		}																				// 9  8  7  6
	}
	else
	{

	}
}

bool Blocks::TestNextLoc(const Board& brd, const Vei2& side) const
{
	return std::any_of(MovingBlocks.begin(), MovingBlocks.end(),
		[&](const BlockSeg& s)
		{
			Vei2 test = s.GetPos() + side;
			return s.GetEmpty() == false && brd.GetCellContent(test) != Board::CellContent::Empty;
		});
}

Blocks::BlockType Blocks::RandomType(std::mt19937& rng)
{
	std::uniform_int_distribution<int> randtype(0, 6);
	int random = randtype(rng);
	if (random == 0)
	{
		type = BlockType::I;
		
	}
	else if (random == 1)
	{
		type = BlockType::N;
	}
	else if (random == 2)
	{
		type = BlockType::L;
	}
	else if (random == 3)
	{
		type = BlockType::HalfCross;
	}
	else if (random == 4)
	{
		type = BlockType::Brick;
	}
	else if (random == 5)
	{
		type = BlockType::MirrorN;
	}
	else if (random == 6)
	{
		type = BlockType::MirrorL;
	}
	return type;
}

Color Blocks::SetColor(const Board& brd)
{
	if (brd.GetLvl() == Board::Levels::Level1)
	{
		if (type == BlockType::Brick)
		{
			c = Colors::Blue;
			ContentColor = Board::CellContent::Blue;
		}
		else if (type == BlockType::L)
		{
			c = Colors::Cyan;
			ContentColor = Board::CellContent::Cyan;
		}
		else if (type == BlockType::HalfCross)
		{
			c = Colors::MidnightBlue;
			ContentColor = Board::CellContent::MidnightBlue;
		}
		else if (type == BlockType::I)
		{
			c = Colors::White;
			ContentColor = Board::CellContent::White;
		}
		else if (type == BlockType::N)
		{
			c = Colors::LightGray;
			ContentColor = Board::CellContent::LightGray;
		}
		else if (type == BlockType::MirrorN)
		{
			c = Colors::Gray;
			ContentColor = Board::CellContent::Gray;
		}
		else if (type == BlockType::MirrorL)
		{
			c = Colors::Teal;
			ContentColor = Board::CellContent::Teal;
		}
	}
	else if (brd.GetLvl() == Board::Levels::Level2)
	{
		if (type == BlockType::Brick)
		{
			c = Colors::Green;
			ContentColor = Board::CellContent::Green;
		}
		else if (type == BlockType::L)
		{
			c = Colors::DarkGreen;
			ContentColor = Board::CellContent::DarkGreen;
		}
		else if (type == BlockType::HalfCross)
		{
			c = Colors::LawnGreen;
			ContentColor = Board::CellContent::LawnGreen;
		}
		else if (type == BlockType::I)
		{
			c = Colors::Yellow;
			ContentColor = Board::CellContent::Yellow;
		}
		else if (type == BlockType::N)
		{
			c = Colors::Lime;
			ContentColor = Board::CellContent::Lime;
		}
		else if (type == BlockType::MirrorN)
		{
			c = Colors::LightGreen;
			ContentColor = Board::CellContent::LightGreen;
		}
		else if (type == BlockType::MirrorL)
		{
			c = Colors::SpringGreen;
			ContentColor = Board::CellContent::SpringGreen;
		}
	}
	else if (brd.GetLvl() == Board::Levels::Level3)
	{
		if (type == BlockType::Brick)
		{
			c = Colors::DarkRed;
			ContentColor = Board::CellContent::DarkRed;
		}
		else if (type == BlockType::L)
		{
			c = Colors::Scarlet;
			ContentColor = Board::CellContent::Scarlet;
		}
		else if (type == BlockType::HalfCross)
		{
			c = Colors::Red;
			ContentColor = Board::CellContent::Red;
		}
		else if (type == BlockType::I)
		{
			c = Colors::Orange;
			ContentColor = Board::CellContent::Orange;
		}
		else if (type == BlockType::N)
		{
			c = Colors::Purple;
			ContentColor = Board::CellContent::Purple;
		}
		else if (type == BlockType::MirrorN)
		{
			c = Colors::DarkMagneta;
			ContentColor = Board::CellContent::DarkMagneta;
		}
		else if (type == BlockType::MirrorL)
		{
			c = Colors::Chocolate;
			ContentColor = Board::CellContent::Chocolate;
		}
	}
	return c;
}

Vei2 Blocks::MostSideBlock(const char m) const
{
	Vei2 pos;
	Vei2 temp;
	bool FirstActive = false;
	for (int i = 0; i < MovingBlocks.size(); i++)
	{
		if (MovingBlocks[i].Empty)
		{
			continue;
		}
		else
		{
			temp = MovingBlocks[i].GetPos();
			if (!FirstActive)
			{
				pos = temp;
				FirstActive = true;
			}
			else
			{
				if (m == 'l')
				{
					if (temp.x < pos.x)
					{
						pos = temp;
					}
					else
					{
						pos = pos;
					}
				}
				if (m == 'r')
				{
					if (temp.x > pos.x)
					{
						pos = temp;
					}
					else
					{
						pos = pos;
					}
				}
				if (m == 'd')
				{
					if (temp.y > pos.y)
					{
						pos = temp;
					}
					else
					{
						pos = pos;
					}
				}
			}
		}
		
	}
	return pos;
}

void Blocks::LevelCheck(const Board& brd)
{
	BlockMoveRateDown = StartSpeed - (0.005f * brd.GetLineNumber());
}


Blocks::BlockSeg::BlockSeg(Vei2& in_pos, Color c)
	:
	pos(in_pos),
	BColor(c)
{
}

void Blocks::BlockSeg::Draw(Board& brd) const
{
	brd.DrawCell(pos, BColor);
}

void Blocks::BlockSeg::Moveby(Vei2& delta_loc)
{
	pos += delta_loc;
}

Vei2 Blocks::BlockSeg::GetPos() const
{
	return pos;
}

Color Blocks::BlockSeg::GetBcolor() const
{
	return BColor;
}

bool Blocks::BlockSeg::GetEmpty() const
{
	return Empty;
}
