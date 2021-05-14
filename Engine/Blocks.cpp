#include "Blocks.h"

Blocks::Blocks(const BlockType& type, Color c)
	:
	StartPos({9, 3})
{
	MovingBlocks.reserve(total);		
	Vei2 loc = StartPos;
	for (int y = 0; y < pysty; y++)
	{
		loc.y += 1;
		for (int x = 0; x < viisto; x++)
		{
			loc.x += 1;
			if (loc.x >= StartPos.x + 3)
			{
				loc.x = StartPos.x;
			}
			int i = y * viisto + x;
			MovingBlocks.emplace_back(loc, c);

			if (type == BlockType::I)
			{
				if (x == 1)
				{
					MovingBlocks[i].Empty = false;
				}
				else
				{
					MovingBlocks[i].Empty = true;
				}
			}



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
		Rotate(BlockType::I);
	}
	else
	{
		delta_loc = { 0, 0 };
	}
}

void Blocks::Rotate(BlockType type)
{
	for (int y = 0; y < pysty; y++)
	{
		for (int x = 0; x < viisto; x++)
		{
			int i = y * viisto + x;
			if (type == BlockType::I)
			{
				if (MovingBlocks[x == 1].Empty)
				{
					MovingBlocks[x == 1].Empty = false;
				}
				else if (MovingBlocks[y == 1].Empty)
				{
					MovingBlocks[y == 1].Empty = false;
				}
			}



		}
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
