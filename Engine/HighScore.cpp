#include "HighScore.h"

HighScore::HighScore()
{
	entries.reserve(4);
	std::ifstream in("Teksti//HighScore.txt");
	int score1 = 0;
	int lines1 = 0;
	int score2 = 0;
	int lines2 = 0;
	int score3 = 0;
	int lines3 = 0;
	in >> score1 >> score2 >> score3 >> lines1 >> lines2 >> lines3;
	entries.emplace_back(score1, lines1);
	entries.emplace_back(score2, lines2);
	entries.emplace_back(score3, lines3);
}

void HighScore::Save(const Board& brd)
{
	int score = brd.GetScore();
	int lines = brd.GetLineNumber();
	std::ifstream in("Teksti//HighScore.txt");

	in >> entries[0].Score >> entries[1].Score >> entries[2].Score >> entries[0].Lines
		>> entries[1].Lines >> entries[2].Lines;

	if (score > entries[0].Score)
	{
		newhighscore = true;
	}
	entries.emplace_back(Entrys(score, lines));

	std::sort(entries.begin(), entries.end(), [](const Entrys& l, const Entrys& r) {return (l.Score > r.Score) ||
		l.Score == r.Score && l.Lines > r.Lines; });

	std::ofstream out("Teksti//HighScore.txt");

	out << entries[0].Score << "\n" << entries[1].Score << "\n" << entries[2].Score << "\n" <<
		entries[0].Lines << "\n" << entries[1].Lines << "\n" << entries[2].Lines;
}

void HighScore::Draw(Graphics& gfx)
{
	Score.DrawTexts("HighScore ", Vei2(200, 100), gfx, Colors::White);

	Score.DrawTexts("1.Score: ", Vei2(100, 150), gfx, Colors::White);
	Score.DrawTexts("  Lines: ", Vei2(100, 180), gfx, Colors::White);

	Score.DrawTexts("2.Score: ", Vei2(100, 220), gfx, Colors::White);
	Score.DrawTexts("  Lines: ", Vei2(100, 250), gfx, Colors::White);

	Score.DrawTexts("3.Score: ", Vei2(100, 290), gfx, Colors::White);
	Score.DrawTexts("  Lines: ", Vei2(100, 320), gfx, Colors::White);

	Vei2 spos = { 330, 150 };
	Vei2 lpos = { 330, 180 };
	for (int i = 0; i < entries.size(); i++)
	{
		if (i > 2)
		{
			break;
		}
		Score.DrawTexts(std::to_string(entries[i].Score), spos, gfx, Colors::White);
		Score.DrawTexts(std::to_string(entries[i].Lines), lpos, gfx, Colors::White);
		spos.y += 70;
		lpos.y += 70;
	}
	/*if (newhighscore)
	{
		Score.DrawTexts("New HighScore", Vei2(500, 200), gfx, Colors::Blue);
	}*/
}

HighScore::Entrys::Entrys(int Score, int Lines)
	:
	Score(Score),
	Lines(Lines)
{
}
