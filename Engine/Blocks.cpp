#include "Blocks.h"

Blocks::Blocks(const Vei2& pos, const BlockType& type, Color c)
{
	if (type == BlockType::I)
	{
		for (int y = 0; y < pysty; y++)
		{
			for (int x = 0; x < viisto; x++)
			{
				int i = y * viisto + x;
				MovingBlocks.emplace_back(pos, c);
				if (y == 2)
				{
					MovingBlocks[i].Empty = true;
				}
				else
				{
					MovingBlocks[i].Empty = false;
				}
			}
		}
	}
}

void Blocks::Draw(Board& brd) const
{
}

void Blocks::MoveBy(Vei2& delta_loc)
{
}

Blocks::BlockSeg::BlockSeg(Vei2& in_pos, Color c)
	:
	pos(in_pos),
	BColor(c)
{
}

void Blocks::BlockSeg::Draw(Board& brd) const
{
}

void Blocks::BlockSeg::Moveby(Vei2& delta_loc)
{
}
