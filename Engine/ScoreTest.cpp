#include "ScoreTest.h"

void ScoreTest::Save(const Board& brd)
{
	Score = brd.GetScore();
	std::ifstream in("Teksti//Test.txt");
	int bestscore;
	in >> bestscore;
	std::ofstream out("Teksti//Test.txt");

	if (Score > bestscore)
	{
		bestscore = Score;
	}
	out << bestscore;
	

}

void ScoreTest::LoadAndDraw(Graphics& gfx)
{
	std::ifstream in("Teksti//Test.txt");
	in >> Score;
	std::string scoretest = std::to_string(Score);
	HighScore.DrawTexts("HighScore: ", Vei2(100, 100), gfx, Colors::White);
	HighScore.DrawTexts(scoretest, Vei2(350, 100), gfx, Colors::White);

}
