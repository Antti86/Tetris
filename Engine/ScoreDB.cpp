#include "ScoreDB.h"

void ScoreDB::LoadAndDrawScore()
{
}

void ScoreDB::SaveScore(const Board& brd)
{
	std::ifstream in("Teksti//Score.txt", std::ios::binary);
	std::string test;
	std::vector<Entry> file;
	int sscore = 0;
	int slines = 0;
	std::stringstream ss;
	for (std::string line; std::getline(in, line);)
	{
		ss.str(line);
		if (line.find("Score:"))
		{
			ss >> sscore;
		}
		else if (line.find("Lines:"))
		{
			ss >> slines;
		}
		if (slines != 0)
		{
			file.emplace_back(Entry(sscore, slines));
		}
	}
	entries.emplace_back(Entry(brd));



	std::ofstream out("Teksti//Score.txt");
	std::string sScore = std::to_string(brd.GetScore());
	std::string sLines = std::to_string(brd.GetLineNumber());



}

ScoreDB::Entry::Entry(const Board& brd)
	:
	Lines(brd.GetLineNumber()),
	Score(brd.GetScore())
{
}

ScoreDB::Entry::Entry(int Score, int Lines)
	:
	Score(Score),
	Lines(Lines)
{
}
