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
		bool Empty = true;
	private:
		Vei2 pos;
		
		Color BColor;
	};

public:
	Blocks(const Vei2& pos, const BlockType& type, Color c);
	void Draw(Board& brd) const;
	void MoveBy(Vei2& delta_loc);


private:
	std::vector<BlockSeg> MovingBlocks;

	static constexpr int viisto = 3;		//vecktorin koko
	static constexpr int pysty = 3;
	static constexpr int total = viisto * pysty;
};