#include "Blocks.h"

Blocks::Blocks(Vei2& StartPos)
	:
	StartPos( StartPos ),
	rng(std::random_device() () )
{
	RandomType(rng);
	RandomColor(rng);
	Vei2 loc = StartPos;

	if (type == BlockType::I)		//2D Grid
	{
		MovingBlocks.reserve(total);
		for (int y = 0; y < Collums; y++)
		{
			loc.y += 1;
			for (int x = 0; x < Rows; x++)
			{
				loc.x += 1;
				MovingBlocks.emplace_back(loc, c);
				if (loc.x >= StartPos.x + Rows)
				{
					loc.x = StartPos.x;
				}
				int i = y * Rows + x;
				if (x == 1)
				{
					MovingBlocks[i].Empty = false;
				}
			}
		}
		std::copy(MovingBlocks.begin(), MovingBlocks.end(), std::back_inserter(StartingPos));
	}
	else
	{
		MovingBlocks.reserve(Linerialtotal);			//Linerial Grid for easier rotation
		for (int i = 0; i < top; i++)					// 0  1  2
		{												// 7  8  3
			loc.x += 1;									// 6  5  4
			MovingBlocks.emplace_back(loc, c);
		}
		for (int t = 0; t < right; t++)					// 0  1  2  3
		{												// 11 12 13 4
			loc.y += 1;									// 10 15 14 5
			MovingBlocks.emplace_back(loc, c);			// 9  8  7  6
		}
		for (int k = 0; k < bottom; k++)
		{
			loc.x -= 1;
			MovingBlocks.emplace_back(loc, c);
		}
		loc.y -= 1;
		for (int j = 0; j < leftandmidlle; j++)
		{
			MovingBlocks.emplace_back(loc, c);
			loc.x += 1;
		}
		std::copy(MovingBlocks.begin(), MovingBlocks.end(), std::back_inserter(StartingPos));
		for (int i = 0; i < Linerialtotal; i++)
		{
			if (type == BlockType::L && (i == 0 || i == 1 || i == 5 || i == 8))
			{
				MovingBlocks[i].Empty = false;
			}
			if (type == BlockType::Brick && (i == 0 || i == 1 || i == 7 || i == 8))
			{
				MovingBlocks[i].Empty = false;
			}
			if (type == BlockType::HalfCross && (i == 1 || i == 5 || i == 7 || i == 8))
			{
				MovingBlocks[i].Empty = false;
			}
			if (type == BlockType::N && (i == 2 || i == 3 || i == 5 || i == 8))
			{
				MovingBlocks[i].Empty = false;
			}
			if (type == BlockType::MirrorN && (i == 0 || i == 5 || i == 7 || i == 8))
			{
				MovingBlocks[i].Empty = false;
			}
			if (type == BlockType::MirrorL && (i == 1 || i == 2 || i == 5 || i == 8))
			{
				MovingBlocks[i].Empty = false;
			}
		}
	}


}

Blocks& Blocks::operator=(const Blocks& b)
{
	//this->type = b.type;
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
		if (!s.Empty)
		{
			s.Draw(brd);
		}
	}
}

Vei2 Blocks::GetNextLoc(const Vei2& delta_loc) const
{
	Vei2 l(MostSideBlock('d'));
	l + delta_loc;
	return l;
}

bool Blocks::CollisionDown(const Board& brd) const
{
	if ( !brd.IsInsideBoard(GetNextLoc(Vei2(0,1))))
	{
		return true;
	}
	else
	{
		return false;
	}
	//brd.GetCellColor(GetNextLoc(Vei2(0, 1))) != Board::CellColor::Empty ||
}


void Blocks::MoveBy(Vei2& delta_loc)
{
	for (auto& s : MovingBlocks)
	{
		s.Moveby(delta_loc);
	}
}

void Blocks::Movement(Vei2& delta_loc, Keyboard& kbd, const Board& brd)
{
	delta_loc = { 0, 1 };
	const Keyboard::Event e = kbd.ReadKey();
	if (kbd.KeyIsPressed(VK_LEFT) && brd.IsInsideBoard(MostSideBlock('l') += {-1, 0}))
	{
		delta_loc = { -1, 0 };
	}
	else if (kbd.KeyIsPressed(VK_RIGHT) && brd.IsInsideBoard(MostSideBlock('r') += {1, 0}))
	{
		delta_loc = { 1, 0 };
	}
	else if (kbd.KeyIsPressed(VK_DOWN))
	{
		BlockMoveCounterDown += 10.0f;
	}
	if (e.IsPress() && e.GetCode() == VK_UP)
	{
		Rotate();
	}
	PositionFix(brd);
	MovementSpeed(delta_loc);

}


void Blocks::MovementSpeed(Vei2& delta_loc)
{
	BlockMoveCounterSide += 2.0f;
	BlockMoveCounterDown += 1.0f;
	if (BlockMoveCounterDown >= BlockMoveRateDown)
	{
		MoveBy(Vei2(0, 1));
		BlockMoveCounterDown = 0;
	}
	if (BlockMoveCounterSide >= BlockMoveRateSide && (delta_loc == Vei2{ -1, 0 } || delta_loc == Vei2{ 1, 0 }))
	{
		MoveBy(delta_loc);
		BlockMoveCounterSide = 0;
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

void Blocks::Rotate()
{
	if (type == BlockType::I)
	{
		std::swap(MovingBlocks[1].Empty, MovingBlocks[4].Empty);
		std::swap(MovingBlocks[9].Empty, MovingBlocks[6].Empty);
		std::swap(MovingBlocks[13].Empty, MovingBlocks[7].Empty);
	}
	else if (type == BlockType::Brick)
	{

	}
	else
	{
		std::vector<BlockSeg> temp;
		std::rotate_copy(MovingBlocks.begin(), MovingBlocks.begin() + 2, MovingBlocks.end() - 1, std::back_inserter(temp));
		for (int i = 0; i < temp.size(); i++)
		{
			MovingBlocks[i].pos = temp[i].pos;
		}
	}
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

Color Blocks::RandomColor(std::mt19937& rng)
{
	std::uniform_int_distribution<int> randtype(0, 3);
	int random = randtype(rng);
	if (random == 0)
	{
		c = Colors::Blue;
	}
	else if (random == 1)
	{
		c = Colors::Green;
	}
	else if (random == 2)
	{
		c = Colors::Red;
	}
	else if (random == 3)
	{
		c = Colors::Yellow;
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


Vei2 Blocks::MostLeftBlockTest()
{
	std::vector<BlockSeg> test;
	std::copy_if(MovingBlocks.begin(), MovingBlocks.end(), std::back_inserter(test),
		[] (BlockSeg& l)
		{
			return l.Empty == false;
		});

	auto n = std::min_element(test.begin(), test.end(),
		[] (BlockSeg& l, BlockSeg& r)
		{
			return l.GetPos().x < r.GetPos().x;
		});

	return n->GetPos();
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
