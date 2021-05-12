#pragma once
#include <vector>
#include "Vec2.h"
#include "Colors.h"
#include <random>
#include "Board.h"
#include "Keyboard.h"
#include <algorithm>

class Blocks
{
public:
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
		Vei2 GetPos() const;
		bool Empty = true;
	private:
		Vei2 pos;
		
		Color BColor;
	};

public:
	Blocks(const BlockType& type, Color c);
	void Draw(Board& brd) const;
	void MoveBy(Vei2& delta_loc);
	void Movement(Vei2& delta_loc, Keyboard& kbd, const Board& brd);
private:
	Vei2 MostLeftBlock() const;
	Vei2 MostLeftBlockTest() const;
private:
	std::vector<BlockSeg> MovingBlocks;
	
	Vei2 StartPos;
	static constexpr int viisto = 3;		//vecktorin koko
	static constexpr int pysty = 3;
	static constexpr int total = viisto * pysty;
};