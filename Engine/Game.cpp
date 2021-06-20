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
	Buffer(Vei2(brd.GetGridWidth() + 4, 4)),
	ActiveBlocks(Vei2(brd.GetGridWidth() / 2 - 2, 0))
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

	
	if (ActiveBlocks.CollisionDown(brd))
	{
		ActiveBlocks.TransferBlocksToBoard(brd);
		ActiveBlocks = Buffer;
		Buffer = Blocks(Vei2(24, 4));
		brd.FullLine();
	}
	else
	{
		ActiveBlocks.Movement(delta_loc, wnd.kbd, brd);
	}


}

void Game::ComposeFrame()
{
	Vei2 test = { 0, 0 };
	gfx.DrawSprite(Vei2(0, 0), s, SpriteEffect::GhostNochroma(0.30));
	brd.DrawBorder();
	brd.DrawBlocks();
	ActiveBlocks.Draw(brd);
	Buffer.DrawOutsideBoard(brd);
}
