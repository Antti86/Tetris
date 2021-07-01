#include "ScoreDB.h"

ScoreDB::ScoreDB()
{
	Load();
}

void ScoreDB::LoadAndDrawScore(Graphics& gfx)
{
	Load();

	std::string FScore = std::to_string(entries[0].Score);
	std::string SScore = std::to_string(entries[1].Score);
	std::string TScore = std::to_string(entries[2].Score);

	std::string FLines = std::to_string(entries[0].Lines);
	std::string SLines = std::to_string(entries[1].Lines);
	std::string TLines = std::to_string(entries[2].Lines);

	HighScore.DrawTexts("HighScore ", Vei2(200, 100), gfx, Colors::White);

	HighScore.DrawTexts("1.Score: ", Vei2(100, 150), gfx, Colors::White);
	HighScore.DrawTexts("1.Lines: ", Vei2(100, 180), gfx, Colors::White);

	HighScore.DrawTexts("2.Score: ", Vei2(100, 220), gfx, Colors::White);
	HighScore.DrawTexts("2.Lines: ", Vei2(100, 250), gfx, Colors::White);

	HighScore.DrawTexts("3.Score: ", Vei2(100, 290), gfx, Colors::White);
	HighScore.DrawTexts("3.Lines: ", Vei2(100, 320), gfx, Colors::White);

	HighScore.DrawTexts(FScore, Vei2(330, 150), gfx, Colors::White);
	HighScore.DrawTexts(FLines, Vei2(330, 180), gfx, Colors::White);

	HighScore.DrawTexts(SScore, Vei2(330, 220), gfx, Colors::White);
	HighScore.DrawTexts(SLines, Vei2(330, 250), gfx, Colors::White);

	HighScore.DrawTexts(TScore, Vei2(330, 290), gfx, Colors::White);
	HighScore.DrawTexts(TLines, Vei2(330, 320), gfx, Colors::White);
}

void ScoreDB::SaveScore(const Board& brd)
{
	entries.reserve(4);
	std::ifstream in("Teksti//Score.txt");
	
	Load();
	entries.emplace_back(Entry(brd));

	std::sort(entries.begin(), entries.end(), [](const Entry& l, const Entry& r) {return l.Score > r.Score; });
	
	std::ofstream out("Teksti//Score.txt");

	for (std::string line; std::getline(in, line);)
	{
		if (line == "1.Score:")
		{
			out << entries[0].Score;
		}
		else if (line == "1.Lines:")
		{
			out << entries[0].Lines;
		}
		else if (line == "2.Score:")
		{
			out << entries[1].Score;
		}
		else if (line == "2.Lines:")
		{
			out << entries[1].Lines;
		}
		else if (line == "3.Score:")
		{
			out << entries[2].Score;
		}
		else if (line == "3.Lines:")
		{
			out << entries[2].Lines;
		}
		else if (line.empty())
		{

		}
		else
		{

		}
	}
}

void ScoreDB::Load()
{
	entries.reserve(3);
	std::ifstream in("Teksti//Score.txt");
	for (std::string line; std::getline(in, line);)
	{
		if (line == "1.Score:")
		{
			in >> score;
		}
		else if (line == "1.Lines:")
		{
			in >> lines;
		}
		else if (line == "2.Score:")
		{
			in >> score;
		}
		else if (line == "2.Lines:")
		{
			in >> lines;
		}
		else if (line == "3.Score:")
		{
			in >> score;
		}
		else if (line == "3.Lines:")
		{
			in >> lines;
		}
		else if (line.empty())
		{

		}
		else
		{

		}
		if (lines != 0 && score != 0)
		{
			entries.emplace_back(Entry(score, lines));
			score = 0;
			lines = 0;
		}
	}
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
