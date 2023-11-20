#include "TwoPlayerMode.h"
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

void TwoPlayerMode::SwapActivePlayer(PlayerManager* mgrRef) const
{
	
	mgrRef->GetActivePlayer()->GetNextPlayer()->SwapFocusToThisPlayer();
	
}

void TwoPlayerMode::CreatePlayers(PlayerManager* mgrRef) const
{
	Player* holdAIPlr = mgrRef->CreatePlayer(ControllerManager::ControlType::AI, mgrRef->PlayerNumber::AI);

	//Make the AI player the starting player of the game
	mgrRef->SetActivePlayer(holdAIPlr);

	holdAIPlr->SetPlayerState((ActivePlayerState*)&ActivePlayerState::aiPlayerState);

	//Create a blaster with the new controller reference passed to it
	//Only the AI player with have a blaster to start the game
	Blaster* blasterRef = BlasterFactory::CreateBlaster(holdAIPlr->GetPlayerController());

	//Set the newly created blaster to represent this player
	holdAIPlr->SetPlayerBlaster(blasterRef);

	//Create human player 1 with the keyboard controller
	Player* holdPlr1 = mgrRef->CreatePlayer(ControllerManager::ControlType::KEYBOARD, mgrRef->PlayerNumber::Player_1);

	holdPlr1->SetPlayerState((ActivePlayerState*)&ActivePlayerState::humanPlayerState);

	holdAIPlr->SetNextPlayer(holdPlr1);

	//Create human player 2 with the keyboard controller
	Player* holdPlr2 = mgrRef->CreatePlayer(ControllerManager::ControlType::KEYBOARD, mgrRef->PlayerNumber::Player_2, holdPlr1);

	holdPlr2->SetPlayerState((ActivePlayerState*)&ActivePlayerState::humanPlayerState);

	//Set player 1's next pointer to point to the second player
	holdPlr1->SetNextPlayer(holdPlr2);
}

const int TwoPlayerMode::GetMaxPlayers() const
{
	return maxPlayers;
}

void TwoPlayerMode::HandleGameOver() const
{
	//Given that scenes will be swapped, tell the game manager that scene processing is halted if it is not already
	if (GameManager::MainSceneProcessing())
	{
		GameManager::ToggleMainSceneProcessingBool();
	}

	//Hold a reference to the next player
	Player* holdNextPlr = GameManager::GetPlayerMgr()->GetActivePlayer()->GetNextPlayer();

	//Make the next player point to the AI player, and will switch to them when they run out of lives
	holdNextPlr->SetNextPlayer(GameManager::GetPlayerMgr()->GetPlayerByEnum(PlayerManager::PlayerNumber::AI));

	//Swap focus to the next player
	holdNextPlr->SwapFocusToThisPlayer();
}

void TwoPlayerMode::HandlePlayerDeath(std::stack<Mushroom*> mushStack) const
{
	Player* holdActivePlr = GameManager::GetPlayerMgr()->GetActivePlayer();

	//When the player runs out of lives, send their score to the high score manager to test if it will go in the high score list
	if (holdActivePlr->GetPlayerLives() <= 0)
	{
		//Change the scene to GameOver mode now that a player has run out of lives
		MushroomRegeneration* mushroomRegenMgr = new MushroomRegeneration(mushStack, (new GameOverScene), false);
	}
	//If the game is in two-player mode, switch to the other player upon one player's death
	else
	{
		//Tell the previously active player to save it's grid data for when it comes back into view
		holdActivePlr->GetPlayerGrid()->StoreGridData();
		holdActivePlr->SetPlayerGridStatus(true);

		//Begin mushroom regeneration and pass it the scene that will begin once it completes
		MushroomRegeneration* mushroomRegenMgr = new MushroomRegeneration(mushStack, (new MainGameScene), true);
	}
}

void TwoPlayerMode::ResetPlayers() const
{
	PlayerManager* holdPlrMgrRef = GameManager::GetPlayerMgr();

	Player* holdAIPlr = holdPlrMgrRef->GetPlayerList().at((int)holdPlrMgrRef->PlayerNumber::AI);
	Player* holdPlr1 = holdPlrMgrRef->GetPlayerList().at((int)holdPlrMgrRef->PlayerNumber::Player_1);
	Player* holdPlr2 = holdPlrMgrRef->GetPlayerList().at((int)holdPlrMgrRef->PlayerNumber::Player_2);

	holdAIPlr->SetNextPlayer(holdPlr1);
	holdPlr1->SetNextPlayer(holdPlr2);
	holdPlr2->SetNextPlayer(holdPlr1);

	holdAIPlr->ResetPlayer();
	holdPlr1->ResetPlayer();
	holdPlr2->ResetPlayer();
}
