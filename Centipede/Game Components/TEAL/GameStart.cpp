// GameStart.cpp
// Andre Berthiaume, July 2019

#include "Game.h"
#include "CommonElements.h"

void Game::GameStart()
{
	//30 columns, 32 rows, 16x16 pixel cells
	WindowManager::SetWindowSize(480, 512);
	WindowManager::SetCaptionName("Centipede");
}
