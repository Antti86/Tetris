#include "ScoreDB.h"

ScoreDB::ScoreDB()
{
	Load();
}

void ScoreDB::LoadAndDrawScore(Graphics& gfx)
{
	//Load();

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
	entries.reserve(5);
	std::ifstream in("Teksti//Score.txt");
	
	std::ostringstream file;
	
	file << in.rdbuf();

	std::string text = file.str();
	std::string searchScore0 = std::to_string(entries[0].Score);
	std::string searchScore1 = std::to_string(entries[1].Score);
	std::string searchScore2 = std::to_string(entries[2].Score);

	std::string searchLine0 = std::to_string(entries[0].Lines);
	std::string searchLine1 = std::to_string(entries[1].Lines);
	std::string searchLine2 = std::to_string(entries[2].Lines);

	size_t posScore0 = text.find(searchScore0);
	size_t posScore1 = text.find(searchScore1);
	size_t posScore2 = text.find(searchScore2);

	size_t posLine0 = text.find(searchLine0);
	size_t posLine1 = text.find(searchLine1);
	size_t posLine2 = text.find(searchLine2);
	
	lines = brd.GetLineNumber();
	score = brd.GetScore();
	entries.emplace_back(Entry(score, lines));

	std::sort(entries.begin(), entries.end(), [](const Entry& l, const Entry& r) {return l.Score > r.Score; });
	
	std::string replaceScore0 = std::to_string(entries[0].Score);
	std::string replaceScore1 = std::to_string(entries[1].Score);
	std::string replaceScore2 = std::to_string(entries[2].Score);

	std::string replaceLine0 = std::to_string(entries[0].Lines);
	std::string replaceLine1 = std::to_string(entries[1].Lines);
	std::string replaceLine2 = std::to_string(entries[2].Lines);

	text.replace(posScore0, std::string(searchScore0).length(), replaceScore0);
	text.replace(posScore1, std::string(searchScore1).length(), replaceScore1);
	text.replace(posScore2, std::string(searchScore2).length(), replaceScore2);

	text.replace(posLine0, std::string(searchLine0).length(), replaceLine0);
	text.replace(posLine1, std::string(searchLine1).length(), replaceLine1);
	text.replace(posLine2, std::string(searchLine2).length(), replaceLine2);
	in.close();
	std::ofstream out("Teksti//Score.txt");
	out << text;
	out.close();

}

void ScoreDB::Load()
{
	entries.reserve(5);
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



ScoreDB::Entry::Entry(int Score, int Lines)
	:
	Score(Score),
	Lines(Lines)
{
}
