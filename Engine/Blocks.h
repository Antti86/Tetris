#pragma once
#include <vector>
#include "Vec2.h"
#include "Colors.h"
#include <random>
#include "Board.h"
#include "Keyboard.h"
#include <algorithm>
#include <iterator>
#include <functional>

class Blocks
{
public:
	enum class BlockType
	{
		I,
		N,
		L,
		HalfCross,
		Brick,
		MirrorN,
		MirrorL
	};

private:
	class BlockSeg
	{
		friend class Blocks;
	public:
		BlockSeg(Vei2& in_pos, Color c);
		void Draw(Board& brd) const;
		void Moveby(Vei2& delta_loc);
		Vei2 GetPos() const;

	private:
		bool Empty = true;
		Vei2 pos;
		Color BColor;
	};

public:
	//Blocks(const BlockType& type, Color c);
	Blocks(const BlockType& type, Color c);
	void Draw(Board& brd) const;
	void MoveBy(Vei2& delta_loc);
	void Movement(Vei2& delta_loc, Keyboard& kbd, const Board& brd);
	void Rotate();
private:
	Vei2 MostSideBlock(const char m) const;
	Vei2 MostLeftBlockTest();
private:
	std::vector<BlockSeg> MovingBlocks;
	BlockType type;
	Vei2 StartPos;
	
	static constexpr int viisto = 4;		//vecktorin koko
	static constexpr int pysty = 4;
	static constexpr int total = viisto * pysty;

	static constexpr int top = 3;
	static constexpr int right = 2;
	static constexpr int bottom = 2;
	static constexpr int leftandmidlle = 2;
	static constexpr int midlle = 1;
	static constexpr int testtotal = top + right + bottom + leftandmidlle;

};