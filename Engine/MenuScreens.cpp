#include "MenuScreens.h"


MenuScreen::MenuScreen(const std::string& text, const Surface& filename, const Vei2& in_textpos)
	:
	menutext(text),
	textpos(in_textpos),
	BackGround(filename),
	menucount(0)
{
	nlines = Menu.GetNumberOfLines(text);
	SetSelectionPos();
}



void MenuScreen::Draw(Graphics& gfx)
{
	SpriteEffect::NoChroma E;
	gfx.DrawSprite(Vei2(0, 0), BackGround, E);
	Menu.DrawTexts(menutext, textpos, gfx, Colors::Red);
	DrawSelectionPointer(gfx, SelPointPos);
}


void MenuScreen::DrawSelectionPointer(Graphics& gfx, const Vei2& StartMenuP) const
{
	gfx.DrawCircle(StartMenuP.x, StartMenuP.y, cRadius, Colors::Blue);
}

void MenuScreen::MenuMovement(const Keyboard::Event& e) 
{
	if (e.GetCode() == VK_UP && menucount > 0)
	{
		menucount -= 1;
	}
	if (e.GetCode() == VK_DOWN && menucount < nlines)
	{
		menucount += 1;
	}
}

void MenuScreen::SetSelectionPos()
{
	SelPointPos.x = textpos.x - 30;
	SelPointPos.y = (textpos.y + (Menu.GetcharHeight() / 2)) + (menucount * Menu.GetcharHeight());
}



MenuScreen::Options MenuScreen::ProcessMenu(Keyboard& kbd) 
{
	SetSelectionPos();
	const Keyboard::Event e = kbd.ReadKey();
	if (e.IsPress())
	{
		MenuMovement(e);
		if (e.GetCode() == VK_RETURN)
		{
			if (menucount == 0)
			{
				return Options::Opt1;
			}
			else if (menucount == 1)
			{
				return Options::Opt2;
			}
			else if (menucount == 2)
			{
				return Options::Opt3;
			}
			else if (menucount == 3)
			{
				return Options::Opt4;
			}
			else if (menucount == 4)
			{
				return Options::Opt5;
			}
			else if (menucount == 5)
			{
				return Options::Opt6;
			}
			else if (menucount == 6)
			{
				return Options::Opt7;
			}
		}
	}
	return Options::Invalid;
}






