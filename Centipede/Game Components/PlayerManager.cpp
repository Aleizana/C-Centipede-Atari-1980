#include "PlayerManager.h"
#include "Player.h"
#include "TEAL/CommonElements.h"
#include "BlasterFactory.h"
#include "ControllerManager.h"
#include "GridManager.h"
#include "Grid.h"
#include "Blaster.h"
#include "MainGameScene.h"
#include "GameManager.h"
#include <assert.h>
#include "SoundCommand.h"
#include "PlaySoundCommand.h"
#include "AttractorMode.h"
#include "SoundManager.h"
#include "ControllerBase.h"
#include "PlayMode.h"
#include "ActivePlayerState.h"

PlayerManager::PlayerManager()
	: activePlayer(nullptr), ctrlMgrRef(nullptr), pActivePlayerState(nullptr), activePlayer_Number(PlayerNumber::AI), pSound(nullptr)
{
}

void PlayerManager::GameStartInit()
{
	pActivePlayerState = (ActivePlayerState*)&ActivePlayerState::aiPlayerState;

	ConsoleMsg::WriteLine("Player manager initialized with controller manager and creating an AI player");

	//Create a controller manager for the game to give controllers to the player objects
	ctrlMgrRef = new ControllerManager();

	CreatePlayersInit();
}

void PlayerManager::CreateAllPlayers()
{
	Player* holdAIPlr = CreatePlayer(ControllerManager::ControlType::AI, PlayerNumber::AI);

	holdAIPlr->SetPlayerState((ActivePlayerState*)&ActivePlayerState::aiPlayerState);

	//Make the AI player the starting player of the game
	SetActivePlayer(holdAIPlr);

	//Create a blaster with the new controller reference passed to it
	//Only the AI player with have a blaster to start the game
	Blaster* blasterRef = BlasterFactory::CreateBlaster(holdAIPlr->GetPlayerController());

	//Set the newly created blaster to represent this player
	holdAIPlr->SetPlayerBlaster(blasterRef);

	//Create human player 1 with the keyboard controller
	Player* holdPlr1 = CreatePlayer(ControllerManager::ControlType::KEYBOARD, PlayerNumber::Player_1);

	holdPlr1->SetPlayerState((ActivePlayerState*)&ActivePlayerState::humanPlayerState);

	//Create human player 2 with the keyboard controller
	Player* holdPlr2 = CreatePlayer(ControllerManager::ControlType::KEYBOARD, PlayerNumber::Player_2);

	holdPlr2->SetPlayerState((ActivePlayerState*)&ActivePlayerState::humanPlayerState);
}

PlayerManager::~PlayerManager()
{
	//Delete each of the players from the game
	for (Player* plr : plrList)
	{
		delete plr;
	}

	delete ctrlMgrRef;
	delete pSound;
}

Player* PlayerManager::CreatePlayer(int controllerEnumVal, PlayerNumber plrNum, Player* nextPlrRef)
{
	ConsoleMsg::WriteLine("Created a new player.");

	//Create a new player and add it to the back of the vector
	Player* newPlr = new Player;

	plrList.push_back(newPlr);

	ConsoleMsg::WriteLine("Created a new grid for the player");
	//Create a new grid for the respective player
	GameGrid* holdNewGrid = GameManager::GetGridMgr()->CreateGrid();
	newPlr->SetPlayerGrid(holdNewGrid);

	newPlr->SetPlayerNum((int)plrNum);

	//Create a new controller for the player
	ControllerBase* holdNewCtrl = ctrlMgrRef->CreateController((ControllerManager::ControlType)controllerEnumVal);

	//Set the player with it's controller
	newPlr->SetPlayerController(holdNewCtrl);

	//Set the value corressponding to the enumeration value of the players controller type
	newPlr->SetControllerEnum(controllerEnumVal);

	newPlr->SetNextPlayer(nextPlrRef);

	ConsoleMsg::WriteLine("Created a new controller and blaster for the player");

	return newPlr;
}

void PlayerManager::CreatePlayersInit()
{
	CreateAllPlayers();
	
	//Sets the pointers of the players appropriate for the game mode
	GameManager::GetPlayMode()->ResetPlayers();
}

Player* PlayerManager::GetActivePlayer()
{
	return activePlayer;
}

Player* PlayerManager::GetPlayerByEnum(PlayerNumber plrNum) const
{
	//Ensure the player index is valid
	assert(plrNum >= 0 && plrNum < GameManager::GetPlayMode()->GetMaxPlayers() && "Invalid player ID");

	//If there is only 1 player active, then the AI is currently being displayed so return that only
	//Or, if the player being requested has not been created yet (the index will be equal to or greater than the list sie) then pass back the score and lives of the base-AI player
	if (plrList.size() == 1 || (size_t)plrNum >= plrList.size())
	{
		return plrList.at((int)PlayerNumber::AI);
	}
	//Else return the requested player
	else
	{
		return plrList.at((int)plrNum);
	}
	
}

void PlayerManager::StartGamePlayerSwap()
{
	pActivePlayerState = (ActivePlayerState*)activePlayer->GetNextPlayer()->GetMyActivePlayerState();

	//Set player pointers appropriate for the play mode
	GameManager::GetPlayMode()->ResetPlayers();

	//Swap to the correct player and start the game
	GameManager::GetPlayMode()->SwapActivePlayer(this);
	
}

void PlayerManager::ResetPlayerSceneChange()
{
	if (activePlayer->GetPlayerGridStatus())
	{
		//Restore the grid data of the player
		activePlayer->GetPlayerGrid()->RestoreGridData();
	}

	//Get the player's controller
	ControllerBase* holdNewCtrl = ctrlMgrRef->GetControllerByEnum((ControllerManager::ControlType)activePlayer->GetControllerEnum());
	holdNewCtrl->Initialize();

	//Create a blaster with the new controller reference passed to it
	Blaster* blasterRef = BlasterFactory::CreateBlaster(holdNewCtrl);

	//Give the player a reference to it's blaster
	activePlayer->SetPlayerBlaster(blasterRef);

	//Give the player a reference to the newly created controller
	activePlayer->SetPlayerController(holdNewCtrl);

	ConsoleMsg::WriteLine("Got the player's controller and a new blaster");
}

void PlayerManager::SwapToAIPlayer()
{
	//The front of the player list contains the AI player, and the enumeration value for "AI" is == 0 which is the front of the list
	activePlayer = plrList.at(plrAI_index);

	activePlayer_Number = AI;

	pActivePlayerState = (ActivePlayerState*)&ActivePlayerState::aiPlayerState;

	plrList.at(plr1_Index)->ResetPlayer();
}

void PlayerManager::SendSoundCommand()
{
	GameManager::GetSoundManager()->SendSoundCmd(pSound);
}

void PlayerManager::StoreSoundCommand()
{
	pSound = GameManager::GetSoundManager()->GetSoundCommand(GameManager::GetSoundManager()->SoundEvents::ExtraLife);
}

const int PlayerManager::GetPlayerAreaLimit()
{
	return playerAreaLimit;
}

std::vector<Player*> PlayerManager::GetPlayerList()
{
	return plrList;
}

void PlayerManager::SetActivePlayer(Player* plrToSet)
{
	activePlayer = plrToSet;
	activePlayer_Number = (PlayerNumber)plrToSet->GetPlayerNumber();

	ConsoleMsg::WriteLine("Swapped to player " + Tools::ToString(activePlayer_Number));

	pActivePlayerState = (ActivePlayerState*)activePlayer->GetMyActivePlayerState();
}

const ActivePlayerState* PlayerManager::GetActivePlayerState()
{
	return pActivePlayerState;
}

const int PlayerManager::GetPlr1Index() const
{
	return plr1_Index;
}

void PlayerManager::SwitchToHumanPlayerState()
{
	pActivePlayerState = (ActivePlayerState*)&ActivePlayerState::humanPlayerState;
}
