#pragma once
#include "Graphics.h"
#include "Surface.h"
#include "Rect.h"
#include "SpriteEffect.h"
#include "Keyboard.h"
#include "Font.h"

class MenuScreen
{
public:
	enum class Options
	{
		Opt1,
		Opt2,
		Opt3,
		Opt4,
		Opt5,
		Opt6,
		Opt7,
		Invalid
	};

public:
	MenuScreen(const std::string& text, const Surface& filename, const Vei2& in_textpos);
	void Draw(Graphics& gfx) const;
	Options ProcessMenu(Keyboard& kbd);
private:
	void DrawSelectionPointer(Graphics& gfx, const Vei2& StartMenuP) const;
	void MenuMovement(const Keyboard::Event& e);
	void SetSelectionPos();
private:
	const Surface& BackGround;
	Font Menu = Font("kuvat//fontsheet.bmp");
	Vei2 textpos;
	int menucount;
	Vei2 SelPointPos;
	int cRadius = 6;
	int nlines;
	std::string menutext;
};


































