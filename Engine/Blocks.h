#pragma once
#include <vector>
#include "Vec2.h"
#include "Colors.h"
#include <random>
#include "Board.h"

class Blocks
{
	enum class BlockType
	{
		I,
		L
	};
private:
	class BlockSeg
	{
	public:
		BlockSeg(Vei2& in_pos, Color c);
		void Draw(Board& brd) const;
		void Moveby(Vei2& delta_loc);
	private:
		Vei2 pos;
		bool Empty = true;
		Color BColor;
	};

public:
	Blocks(const Vei2& pos, const BlockType& type);
	void Draw(Board& brd) const;
	void MoveBy(Vei2& delta_loc);


private:
	std::vector<BlockSeg> MovingBlocks;

	static constexpr int x = 3;		//vecktorin koko
	static constexpr int y = 3;
	static constexpr int total = x * y;
};