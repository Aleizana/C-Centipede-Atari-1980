// Game.h
// Andre Berthiaume, Juen 2012
// July 2019: memory clean up & Game start/end
//
// Main game loop

#include "Game.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "Tools.h"
#include "TEALShow.h"
#include "../PlayerManager.h"
#include "../GameManager.h"

using namespace std;

const sf::Keyboard::Key Game::KILLGAMEKEY = sf::Keyboard::Escape;
Game* Game::gameInstance = NULL;

void Game::Run()
{
	// Seed the random generator (Haven't found a more logical spot for it yet...)
	srand((unsigned)time(0));

	// Game Start
	GameStart();

	// Set up the window 
	WindowManager::Initialize();

	// Load resources
	ResourceManager::LoadAllResources();

	while (WindowManager::Window().isOpen() && ! sf::Keyboard::isKeyPressed( KILLGAMEKEY ) )
    {	
		// Adjust game time clock
		Instance().gameclock.ProcessTime();

		// Actual frame processing
		SceneManager::ProcessOneFrame();
	}

	Instance().TerminateGame();

	// Game End
	GameEnd();
}

void Game::TerminateGame()
{
	// Clean up the managers
	GameManager::ToggleMainSceneProcessingBool();	//Halt game processing
	SceneManager::Terminate();
	WindowManager::Terminate();
	TEALShow::Terminate();
	ResourceManager::UnloadAllResources();

	// Clean up the game instance;
	delete gameInstance;
	gameInstance = NULL;
}