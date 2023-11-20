#include "OnePlayerMode.h"
#include "GameManager.h"
#include "PlayerManager.h"
#include "Player.h"
#include "Blaster.h"
#include "Grid.h"
#include <vector>
#include "MainGameScene.h"
#include "AttractorMode.h"
#include "MushroomRegeneration.h"
#include "GameOverScene.h"
#include "Mushroom.h"
#include "ControllerManager.h"
#include "BlasterFactory.h"
#include "ActivePlayerState.h"

void OnePlayerMode::SwapActivePlayer(PlayerManager* mgrRef) const
{
	mgrRef->GetActivePlayer()->GetNextPlayer()->SwapFocusToThisPlayer();
}

void OnePlayerMode::CreatePlayers(PlayerManager* mgrRef) const
{
	//Create the AI player to start the game
	Player* holdAIPlr = mgrRef->CreatePlayer(ControllerManager::ControlType::AI, mgrRef->PlayerNumber::AI);

	//Make the AI player the starting player of the game
	mgrRef->SetActivePlayer(holdAIPlr);

	holdAIPlr->SetPlayerState((ActivePlayerState*)&ActivePlayerState::aiPlayerState);

	//Create a blaster with the new controller reference passed to it
	//Only the AI player with have a blaster to start the game
	Blaster* blasterRef = BlasterFactory::CreateBlaster(holdAIPlr->GetPlayerController());

	//Set the newly created blaster to represent this player
	holdAIPlr->SetPlayerBlaster(blasterRef);

	//Create a human player with the keyboard controller
	Player* holdHumanPlr = mgrRef->CreatePlayer(ControllerManager::ControlType::KEYBOARD, mgrRef->PlayerNumber::Player_1, holdAIPlr);

	holdHumanPlr->SetPlayerState((ActivePlayerState*)&ActivePlayerState::humanPlayerState);

	//The AI player will serve as the head of the list
	holdAIPlr->SetNextPlayer(holdHumanPlr);
}

const int OnePlayerMode::GetMaxPlayers() const
{
	return maxPlayers;
}

void OnePlayerMode::HandleGameOver() const
{
	if (GameManager::MainSceneProcessing())
	{
		GameManager::ToggleMainSceneProcessingBool();
	}

	GameManager::GetPlayerMgr()->GetActivePlayer()->ResetPlayer();

	//Switch back to the AI player now that the player is dead
	GameManager::GetPlayerMgr()->SwapToAIPlayer();

	//Change the scene to attractor mode now that the single player must restart
	SceneManager::ChangeScene(new AttractorMode);
}

void OnePlayerMode::HandlePlayerDeath(std::stack<Mushroom*> mushStack) const
{
	if (GameManager::MainSceneProcessing())
	{
		GameManager::ToggleMainSceneProcessingBool();
	}

	//When the player runs out of lives, send their score to the high score manager to test if it will go in the high score list
	if (GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerLives() <= 0)
	{
		//Change the scene to GameOver mode now that a player has run out of lives
		MushroomRegeneration* mushroomRegenMgr = new MushroomRegeneration(mushStack, (new GameOverScene), false);
	}
	//If the player has more lives and the game is in single player, reset their level
	else
	{
		//Store the player's grid data
		GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->StoreGridData();
		GameManager::GetPlayerMgr()->GetActivePlayer()->SetPlayerGridStatus(true);

		//Begin mushroom regeneration and pass it the scene that will begin once it completes
		MushroomRegeneration* mushroomRegenMgr = new MushroomRegeneration(mushStack, (new MainGameScene), false);
	}
}

void OnePlayerMode::ResetPlayers() const
{
	Player* plrAIRef = GameManager::GetPlayerMgr()->GetPlayerList().at((int)GameManager::GetPlayerMgr()->PlayerNumber::AI);
	Player* plr1Ref = GameManager::GetPlayerMgr()->GetPlayerList().at((int)GameManager::GetPlayerMgr()->PlayerNumber::Player_1);
	

	plrAIRef->SetNextPlayer(plr1Ref);
	plr1Ref->SetNextPlayer(plrAIRef);

	plrAIRef->ResetPlayer();
	plr1Ref->ResetPlayer();
}
