#include "Blocks.h"

Blocks::Blocks(const Vei2& pos, const BlockType& type)
{
	if (type == BlockType::I)
	{
		
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
