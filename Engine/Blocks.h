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
public:
	enum class Levels
	{
		Level1,
		Level2,
		Level3
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
		Color GetBcolor() const;
		bool GetEmpty() const;
	private:
		bool Empty = true;
		Vei2 pos;
		Color BColor;
	};

public:
	Blocks(Vei2 StartPos);
	Blocks& operator =(const Blocks& b);
	Blocks(const Blocks&) = delete;
	void Draw(Board& brd) const;
	void DrawOutsideBoard(Board& brd) const;
	void Movement(Vei2& delta_loc, Keyboard& kbd, const Board& brd);
	bool CollisionDown(const Board& brd) const;
	void TransferBlocksToBoard(Board& brd);
	void LevelCheck(const Board& brd);
private:
	Vei2 GetNextLoc(const Vei2& delta_loc, char m) const;   //ketjuttaa charin kautta toistaseks
	void MoveBy(Vei2 delta_loc);
	void MovementSpeed(Vei2& delta_loc);
	void PositionFix(const Board& brd);
	void Rotate(const Board& brd);
	bool TestNextLoc(const Board& brd, const Vei2& side) const;
	BlockType RandomType(std::mt19937& rng);
	Color RandomColor(std::mt19937& rng);
	Vei2 MostSideBlock(const char m) const;
private:
	std::vector<BlockSeg> MovingBlocks;
	std::vector<BlockSeg> StartingPos;
	BlockType type;
	Vei2 StartPos;
	std::mt19937 rng;
	Color c;
	Board::CellContent ContentColor;
	Levels lvl;

	float BlockMoveRateDown = 45.0f;		//speed settings
	float BlockMoveCounterDown = 0;

	float BlockMoveRateSide = 40.0f;
	float BlockMoveCounterSide = 0;

	static constexpr int top = 4;			//Block mapping
	static constexpr int right = 3;
	static constexpr int bottom = 3;
	static constexpr int left = 2;
	static constexpr int midlle = 4;
	static constexpr int Linerialtotal = top + right + bottom + left + midlle;
	
};