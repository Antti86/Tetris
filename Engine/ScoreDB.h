#pragma once
#include <fstream>
#include <ostream>
#include <vector>
#include <string>
#include "Font.h"
#include "Board.h"


class ScoreDB
{
private:
	class Entry
	{
	public:
		Entry(const Board& brd);

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