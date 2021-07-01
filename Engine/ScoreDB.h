#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "Font.h"
#include "Board.h"
#include <sstream>
#include <algorithm>


class ScoreDB
{
private:
	class Entry
	{
		friend class ScoreDB;
	public:
		Entry(const Board& brd);
		Entry(int Score, int Lines);
	private:
		int Score;
		int Lines;
	};
public:
	ScoreDB();
	void LoadAndDrawScore(Graphics& gfx);
	void SaveScore(const Board& brd);
private:
	void Load();
	std::vector<Entry> entries;
	Font HighScore = { "kuvat//Consolas13x24.bmp" };
	int score = 0;
	int lines = 0;
};