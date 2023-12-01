#include "Player.h"
#include "PlayerManager.h"
#include "Blaster.h"
#include "../Game Components/TEAL/Scene.h"
#include "GameManager.h"
#include "HUDManager.h"
#include "ActivePlayerState.h"
#include "ScoreManager.h"
#include "Grid.h"

Player::Player()
	: lives(startingLives), score(0), waveNum(1), myBlaster(nullptr), gridRef(nullptr), storedGrid(false), myPlayerNum(0), ctrlRef(nullptr), controllerEnumVal(0), extraLifeCounter(1),
		pNextPlayer(nullptr), pActivePlayerState(nullptr)
{
}

void Player::ResetPlayer()
{
	lives = startingLives;
	score = 0;
	waveNum = 1;
	myBlaster = nullptr;
	gridRef->ResetGrid();
	storedGrid = false;
	ctrlRef = nullptr;
	extraLifeCounter = 1;
}

void Player::AddScoreToPlayer(int val)
{
	score += val;

	//If the score has reached the extra life score limit times the multiplier 
	if (score >= GameManager::GetScoreMgr()->GetScoreForExtraLife() * extraLifeCounter)
	{
		//Play the sound effect for extra life
		GameManager::GetPlayerMgr()->SendSoundCommand();

		//Increment the number of lifes
		lives++;

		//Increment the multiplier for the score needed to get an extra life
		extraLifeCounter++;

		//Updates the score and lives display but pass in the new amount of lives
		GameManager::GetHUDManager()->ChangeLivesDisplay(lives);
	}
	else
	{
		//Update the display of the player's score
		GameManager::GetHUDManager()->ChangeScoreDisplay(score);
	}


}

const int Player::GetPlayerScore() const
{
	return score;
}

void Player::SetPlayerBlaster(Blaster* blstrRef)
{
	myBlaster = blstrRef;
}

Blaster* Player::GetPlayerBlaster()
{
	if (myBlaster != nullptr)
	{
		return myBlaster;
	}
	else
	{
		return nullptr;
	}

}

void Player::SetPlayerGrid(GameGrid* setGrid)
{
	gridRef = setGrid;
}

GameGrid* Player::GetPlayerGrid()
{
	return gridRef;
}

bool Player::GetPlayerGridStatus()
{
	return storedGrid;
}

void Player::SetPlayerGridStatus(bool activeGridData)
{
	storedGrid = activeGridData;
}

int Player::GetPlayerWaveNum()
{
	return waveNum;
}

void Player::IncrementPlayerWaveNum()
{
	ConsoleMsg::WriteLine("Player " + Tools::ToString(myPlayerNum) + " beat wave " + Tools::ToString(waveNum) + "!");

	waveNum++;
}

void Player::ResetWaveCount()
{
	ConsoleMsg::WriteLine("Player " + Tools::ToString(myPlayerNum) + " reset wave count!");

	waveNum = 1;
}

void Player::DecrementPlayerLives()
{
	ConsoleMsg::WriteLine("Player " + Tools::ToString(myPlayerNum) + " lost a life! (" + Tools::ToString(lives) + " left!)");

	lives--;
}

const int Player::GetPlayerLives() const
{
	return lives;
}

int Player::GetPlayerNumber()
{
	return myPlayerNum;
}

void Player::SetPlayerNum(int setNum)
{
	myPlayerNum = setNum;
}

void Player::SetPlayerController(ControllerBase* setCtrlRef)
{
	ctrlRef = setCtrlRef;
}

ControllerBase* Player::GetPlayerController() const
{
	return ctrlRef;
}

void Player::SetControllerEnum(int setNum)
{
	controllerEnumVal = setNum;
}

int Player::GetControllerEnum()
{
	return controllerEnumVal;
}

void Player::SetNextPlayer(Player* nextPlrRef)
{
	pNextPlayer = nextPlrRef;
}


Player* Player::GetNextPlayer()
{
	return pNextPlayer;
}


void Player::SwapFocusToThisPlayer()
{
	pActivePlayerState->HandlePlayerSwap(this);
}

void Player::SetPlayerState(const ActivePlayerState* plrState)
{
	pActivePlayerState = (ActivePlayerState*)plrState;
}

const ActivePlayerState* Player::GetMyActivePlayerState()
{
	return pActivePlayerState;
}
