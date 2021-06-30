#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "Font.h"
#include "Board.h"
#include <sstream>


class ScoreDB
{
private:
	class Entry
	{
	public:
		Entry(const Board& brd);
		Entry(int Score, int Lines);
	private:
		int Score;
		int Lines;
	};
public:
	void LoadAndDrawScore();
	void SaveScore(const Board& brd);
private:
	std::vector<Entry> entries;

};