#include "ScoreDB.h"

void ScoreDB::LoadAndDrawScore()
{
}

void ScoreDB::SaveScore(const Board& brd)
{
	
}

ScoreDB::Entry::Entry(const Board& brd)
	:
	Lines(brd.GetLineNumber()),
	Score(brd.GetScore())
{
}
