#include "ScoreTest.h"

void ScoreTest::Save(const Board& brd)
{
	FirstScore = brd.GetScore();
	std::ifstream in("Teksti//Test.txt");
	int bestscore;
	int second;
	in >> bestscore >> second;
	std::ofstream out("Teksti//Test.txt");

	if (FirstScore > bestscore)
	{
		second = bestscore;
		bestscore = FirstScore;
	}
	out << bestscore << "\n" << second;
	

}

void ScoreTest::LoadAndDraw(Graphics& gfx)
{
	std::ifstream in("Teksti//Test.txt");
	in >> FirstScore >> SecondScore;
	std::string scoretest = std::to_string(FirstScore);
	std::string scoretest2 = std::to_string(SecondScore);
	HighScore.DrawTexts("HighScore: ", Vei2(100, 100), gfx, Colors::White);
	HighScore.DrawTexts(scoretest, Vei2(350, 100), gfx, Colors::White);
	HighScore.DrawTexts(scoretest2, Vei2(350, 200), gfx, Colors::White);

}
