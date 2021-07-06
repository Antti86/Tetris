/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	Buffer(Vei2(brd.GetGridWidth() + 4, 4), brd),
	ActiveBlocks(Vei2(brd.GetGridWidth() / 2 - 2, 0), brd)
{
}

void Game::Go()
{
	gfx.BeginFrame();
	
	float elapsedtime = ft.Mark();
	while (elapsedtime > 0.0f)
	{
		float dt = std::min(0.0025f, elapsedtime);
		UpdateModel(dt);
		elapsedtime -= dt;
	}

	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{

	if (state == GameState::MainMenu)
	{
		MenuScreen::Options s = StartMenu.ProcessMenu(wnd.kbd);
		switch (s)
		{
		case MenuScreen::Options::Opt1:
			state = GameState::Playing;
			break;
		case MenuScreen::Options::Opt2:
			state = GameState::HighScore;
			break;
		case MenuScreen::Options::Opt3:
			wnd.Kill();
			break;
		}
	}
	else if(state == GameState::Playing)
	{
		
		if (ActiveBlocks.CollisionDown(brd))
		{
			ActiveBlocks.Movement(delta_loc, wnd.kbd, brd, dt);
			ActiveBlocks.TransferBlocksToBoard(brd);
			ActiveBlocks = Buffer;
			Buffer = Blocks(Vei2(brd.GetGridWidth() / 2 - 2, 0), brd);
			brd.FullLine();
		}
		else
		{
			ActiveBlocks.Movement(delta_loc, wnd.kbd, brd, dt);
		}
		if (brd.FailCondition())
		{
			state = GameState::GameOver;
		}
	}
	else if (state == GameState::HighScore)
	{
		const Keyboard::Event e = wnd.kbd.ReadKey();
		if (e.IsPress() && e.GetCode() == VK_RETURN)
		{
			state = GameState::MainMenu;
		}
	}
	else if (state == GameState::GameOver)
	{
		const Keyboard::Event e = wnd.kbd.ReadKey();
		if (e.IsPress() && e.GetCode() == VK_RETURN)
		{
			Score.Save(brd);
			state = GameState::MainMenu;
			brd.ResetBoard();
			ActiveBlocks = Blocks(Vei2(brd.GetGridWidth() / 2 - 2, 0), brd);
			Buffer = Blocks(Vei2(brd.GetGridWidth() / 2 - 2, 0), brd);
		}
	}



}

void Game::ComposeFrame()
{
	if (state == GameState::MainMenu)
	{
		StartMenu.DrawWithOutBackground(gfx);
	}
	else if(state == GameState::Playing)
	{
		brd.DrawBorder();
		brd.DrawBlocks();
		Score.DrawScore(brd, gfx);
		ActiveBlocks.Draw(brd);
		Buffer.DrawOutsideBoard(brd);
	}
	else if (state == GameState::HighScore)
	{
		Score.DrawHighScoreScreen(gfx);
	}
	else if (state == GameState::GameOver)
	{
		Score.DrawScore(brd, gfx);
		SpriteEffect::NoChroma E;
		gfx.DrawSprite(Vei2(250, 200), gameover, E);
	}

}
