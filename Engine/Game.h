/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Board.h"
#include "Blocks.h"
#include "FrameTimer.h"
#include <random>
#include "Surface.h"
#include "SpriteEffect.h"
#include "MenuScreens.h"
#include "Bencher.h"
#include "HighScore.h"
#include "GameSettings.h"


class Game
{
	enum class GameState
	{
		MainMenu,
		Playing,
		HighScore,
		Settings,
		GameOver
	};
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float dt);
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	/********************************/
	Bencher time;
	FrameTimer ft;
	MenuScreen StartMenu = { " Play\n HighScore\n Settings\n Quit", Vei2(100, 100), Colors::White, Colors::Red };
	Surface gameover = { "kuvat//game_over.bmp" };
	Board brd = { gfx, Vei2(280, 20) };
	Vei2 delta_loc = { 0, 0 };
	Blocks ActiveBlocks;
	Blocks Buffer;
	GameState state = GameState::MainMenu;
	HighScore Score;
	GameSettings settings;
};