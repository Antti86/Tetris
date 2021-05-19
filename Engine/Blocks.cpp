#include "Blocks.h"

/*Blocks::Blocks(const BlockType& type, Color c)
	:
	StartPos({9, 3}),
	type(type)
{
	MovingBlocks.reserve(total);		
	Vei2 loc = StartPos;
	for (int y = 0; y < pysty; y++)
	{
		loc.y += 1;
		for (int x = 0; x < viisto; x++)
		{
			loc.x += 1;
			MovingBlocks.emplace_back(loc, c);
			if (loc.x >= StartPos.x + viisto)
			{
				loc.x = StartPos.x;
			}
			int i = y * viisto + x;
			
			if (type == BlockType::I)
			{
				if (x == 1)
				{
					MovingBlocks[i].Empty = false;
				}
			}
			if (type == BlockType::L)
			{
				if ((x == 1 && y != 3) || i == 0)
				{
					MovingBlocks[i].Empty = false;
				}
			}


		}
	}

}*/

Blocks::Blocks(const BlockType& type, Color c)
	:
	StartPos({9, 3}),
	type(type)
{
	MovingBlocks.reserve(testtotal);
	Vei2 loc = StartPos;
	for (int i = 0; i < top; i++)
	{
		loc.x += 1;
		MovingBlocks.emplace_back(loc, c);
	}
	for (int t = 0; t < right; t++)
	{
		loc.y += 1;
		MovingBlocks.emplace_back(loc, c);
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
	for (int i = 0; i < testtotal; i++)
	{
		if (type == BlockType::L && i == 0 || i == 1 || i == 5 || i == 8)
		{
			MovingBlocks[i].Empty = false;
		}
	}

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

void Blocks::MoveBy(Vei2& delta_loc)
{
	for (auto& s : MovingBlocks)
	{
		s.Moveby(delta_loc);
	}
}

void Blocks::Movement(Vei2& delta_loc, Keyboard& kbd, const Board& brd)
{

	if (kbd.KeyIsPressed(VK_LEFT) && brd.IsInsideBoard(MostSideBlock('l') += {-1, 0}))
	{
		delta_loc = {-1, 0};
	}
	else if (kbd.KeyIsPressed(VK_RIGHT) && brd.IsInsideBoard(MostSideBlock('r') += {1, 0}))
	{
		delta_loc = { 1, 0 };
	}
	else if (kbd.KeyIsPressed(VK_UP))
	{

		std::rotate(MovingBlocks.begin(), MovingBlocks.begin() + 2, MovingBlocks.end() - 1);
		
		/*RotationCount += 1;
		if (RotationCount >= 1)
		{
			RotationCount = 0;
		}
		RotationTest();*/
	}
	else
	{
		delta_loc = { 0, 0 };
	}
}

void Blocks::Rotate()
{
	switch (type)
	{
	case BlockType::I:
		std::swap(MovingBlocks[1].Empty, MovingBlocks[4].Empty);
		std::swap(MovingBlocks[9].Empty, MovingBlocks[6].Empty);
		std::swap(MovingBlocks[13].Empty, MovingBlocks[7].Empty);
		break;
	case BlockType::L:
		std::swap(MovingBlocks[1].Empty, MovingBlocks[4].Empty);
		std::swap(MovingBlocks[9].Empty, MovingBlocks[6].Empty);
		
		switch (RotationCount)
		{
		case 0:
			std::swap(MovingBlocks[8].Empty, MovingBlocks[0].Empty);
			break;
		case 1:
			std::swap(MovingBlocks[0].Empty, MovingBlocks[2].Empty);
			break;
		case 2:
			std::swap(MovingBlocks[2].Empty, MovingBlocks[10].Empty);
			break;
		case 3:
			std::swap(MovingBlocks[10].Empty, MovingBlocks[0].Empty);
			break;
		}
		break;


	

	

	} 
	// 0  1  2  3
	// 4  5  6  7
	// 8  9  10 11
	// 12 13 14 15

	// 12   8   4   0
	// 13   9   5   1
	// 14  10   6   2
	// 15  11   7   3

}

void Blocks::RotationTest()
{
	switch (RotationCount)
	{
	case 0:
		std::rotate(MovingBlocks.begin(), MovingBlocks.end() - 1, MovingBlocks.begin() + 2);
		break;
	case 1:
		std::swap(MovingBlocks[0].Empty, MovingBlocks[2].Empty);
		break;
	case 2:
		std::swap(MovingBlocks[2].Empty, MovingBlocks[10].Empty);
		break;
	case 3:
		std::swap(MovingBlocks[10].Empty, MovingBlocks[0].Empty);
		break;
	}
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
			}
		}
		
	}
	return pos;
}

Blocks::RotationPos Blocks::GetRotPos()
{
	switch (RotationCount)
	{
	case 0:
		clock = RotationPos::Twelve;
		break;
	case 1:
		clock = RotationPos::Three;
		break;
	case 2:
		clock = RotationPos::Six;
		break;
	case 3:
		clock = RotationPos::Nine;
		break;
	}
	return clock;
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
