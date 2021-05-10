#include "Blocks.h"

Blocks::Blocks(const BlockType& type, Color c)
	:
	StartPos({9, 3})
{
	MovingBlocks.reserve(total);
	Vei2 loc = StartPos;
	if (type == BlockType::I)
	{
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
				if (x == 1)
				{
					MovingBlocks[i].Empty = false;
				}
				else
				{
					MovingBlocks[i].Empty = true;
				}
				
			}
			//bricks.emplace_back(Brick(RectF(topleft + Vec2(x * brickWidth, y * brickHeight),
				//brickWidth, brickHeight), c));
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
