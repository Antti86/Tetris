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
	Blocks(Vei2& StartPos);
	Blocks& operator =(const Blocks& b);
	void Draw(Board& brd) const;
	void Movement(Vei2& delta_loc, Keyboard& kbd, const Board& brd);
	bool CollisionDown(const Board& brd) const;
private:
	Vei2 GetNextLoc(const Vei2& delta_loc) const;
	void MoveBy(Vei2& delta_loc);
	void MovementSpeed(Vei2& delta_loc);
	void PositionFix(const Board& brd);
	void Rotate();
	BlockType RandomType(std::mt19937& rng);
	Color RandomColor(std::mt19937& rng);
	Vei2 MostSideBlock(const char m) const;
	Vei2 MostLeftBlockTest();
private:
	std::vector<BlockSeg> MovingBlocks;
	std::vector<BlockSeg> StartingPos;
	BlockType type;
	Vei2 StartPos;
	std::mt19937 rng;
	Color c;
	float BlockMoveRateDown = 30.0f;
	float BlockMoveCounterDown = 0;

	float BlockMoveRateSide = 30.0f;
	float BlockMoveCounterSide = 0;

	//vecktor size
	static constexpr int Rows = 4;		//Block I
	static constexpr int Collums = 4;
	static constexpr int total = Rows * Collums;

	static constexpr int top = 3;			//Other Blocks
	static constexpr int right = 2;
	static constexpr int bottom = 2;
	static constexpr int leftandmidlle = 2;
	static constexpr int midlle = 1;
	static constexpr int Linerialtotal = top + right + bottom + leftandmidlle;

};