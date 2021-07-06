#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "Font.h"
#include "Board.h"
#include <sstream>
#include <algorithm>

class HighScore
{
private:
	class Entrys
	{
		friend class HighScore;
	public:
		Entrys(int Score, int Lines);
	private:
		int Score;
		int Lines;
	};
public:
	HighScore();
	void Save(const Board& brd);
	void DrawHighScoreScreen(Graphics& gfx);
	void DrawScore(const Board& brd, Graphics& gfx) const;
private:
	std::vector<Entrys> entries;
	Font Score = { "kuvat//Consolas13x24.bmp" };
	bool newhighscore = false;
};