#include "ScoreDB.h"

ScoreDB::ScoreDB()
{
	Load();
}

void ScoreDB::LoadAndDrawScore(Graphics& gfx)
{

	HighScore.DrawTexts("HighScore ", Vei2(200, 100), gfx, Colors::White);

	HighScore.DrawTexts("1.Score: ", Vei2(100, 150), gfx, Colors::White);
	HighScore.DrawTexts("  Lines: ", Vei2(100, 180), gfx, Colors::White);

	HighScore.DrawTexts("2.Score: ", Vei2(100, 220), gfx, Colors::White);
	HighScore.DrawTexts("  Lines: ", Vei2(100, 250), gfx, Colors::White);

	HighScore.DrawTexts("3.Score: ", Vei2(100, 290), gfx, Colors::White);
	HighScore.DrawTexts("  Lines: ", Vei2(100, 320), gfx, Colors::White);

	Vei2 spos = { 330, 150 };
	Vei2 lpos = { 330, 180 };
	for (int i = 0; i < entries.size(); i++)
	{
		if (i > 2)
		{
			break;
		}
		HighScore.DrawTexts(std::to_string(entries[i].Score), spos, gfx, Colors::White);
		HighScore.DrawTexts(std::to_string(entries[i].Lines), lpos, gfx, Colors::White);
		spos.y += 70;
		lpos.y += 70;

	}

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

	size_t posScore0 = text.find(searchScore0, 0);
	size_t posScore1 = text.find(searchScore1, 43);
	size_t posScore2 = text.find(searchScore2, 72 );

	size_t posLine0 = text.find(searchLine0, 28);
	size_t posLine1 = text.find(searchLine1, 61);
	size_t posLine2 = text.find(searchLine2, 94);
	
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

	text.replace(posScore0, std::string(replaceScore0).length(), replaceScore0);
	text.replace(posLine0, std::string(replaceLine0).length(), replaceLine0);
	text.replace(posScore1, std::string(replaceScore1).length(), replaceScore1);
	text.replace(posLine1, std::string(replaceLine1).length(), replaceLine1);
	text.replace(posScore2, std::string(replaceScore2).length(), replaceScore2);
	text.replace(posLine2, std::string(replaceLine2).length(), replaceLine2);


	/*text.replace(posScore0, std::string(searchScore0).length(), replaceScore0);
	text.replace(posLine0, std::string(searchLine0).length(), replaceLine0);
	text.replace(posScore1, std::string(searchScore1).length(), replaceScore1);
	text.replace(posLine1, std::string(searchLine1).length(), replaceLine1);
	text.replace(posScore2, std::string(searchScore2).length(), replaceScore2);
	text.replace(posLine2, std::string(searchLine2).length(), replaceLine2);*/
	
	
	
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
		if (line == "First.Score:")
		{
			in >> score;
		}
		else if (line == "First.Lines:")
		{
			in >> lines;
		}
		else if (line == "Second.Score:")
		{
			in >> score;
		}
		else if (line == "Second.Lines:")
		{
			in >> lines;
		}
		else if (line == "Third.Score:")
		{
			in >> score;
		}
		else if (line == "Third.Lines:")
		{
			in >> lines;
		}
		else if (line.empty())
		{

		}
		else
		{
			throw std::runtime_error("file problem");
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

