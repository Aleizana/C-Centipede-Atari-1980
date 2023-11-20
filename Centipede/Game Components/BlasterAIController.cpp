#include "BlasterAIController.h"
#include "Blaster.h"
#include "BlasterFactory.h"
#include "DartFactory.h"
#include "PlayerManager.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "MoveFSM.h"
#include "BlasterAIMoveStateBase.h"
#include "BlasterAIMoveCollection.h"
#include "GridManager.h"

BlasterAIController::BlasterAIController()
{
	ConsoleMsg::WriteLine("Created blaster AI controller");

	pCurrMoveState = (BlasterAIMoveState*)&MoveFSM::StateBlasterAIMoveUpDiagLeft;

	moveArrIncrementor = 0;
}

void BlasterAIController::Destroy()
{
}

void BlasterAIController::Initialize()
{
	ConsoleMsg::WriteLine("Init blaster AI controller");

	pCurrMoveState = (BlasterAIMoveState*)&MoveFSM::StateBlasterAIMoveUpDiagLeft;

	moveArrIncrementor = 0;
}

void BlasterAIController::Update(sf::Vector2f& impulse, Blaster* playerRef)
{
	//Locally set impulse so that the ship will only move while movement inputs are detected
	impulse.x = ImpulseReset;
	impulse.y = ImpulseReset;

	//Add the movement offset to the impulse times the speed of the AI controller
	impulse.x += pCurrMoveState->GetMoveOffsets()[moveArrIncrementor].GetColOffset() * AISpeedRef;
	impulse.y += pCurrMoveState->GetMoveOffsets()[moveArrIncrementor].GetRowOffset() * AISpeedRef;

	playerRef->MoveBlaster(impulse);

	//Increment offset index
	moveArrIncrementor++;

	//if the movement array has been finished, get the next movement
	if (moveArrIncrementor >= BlasterAIMoveCollection::arrMax)
	{
		pCurrMoveState = pCurrMoveState->GetNextState();
		moveArrIncrementor = 0;

		//Fire a dart whenever the offset max is reached
		DartFactory::CreateDart(playerRef->GetPos());
	}

	
}

void BlasterAIController::KeyPressed(Blaster* playerRef, sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey)
{
	//Player input to end the AI input and start the game with full controls
	if (k == sf::Keyboard::Enter)
	{
		ConsoleMsg::WriteLine("Swapping to real player");

		//Swap to a human player to start the game
		GameManager::GetPlayerMgr()->StartGamePlayerSwap();
	}
	//Mutes/Unmutes the game when pressed
	else if (k == sf::Keyboard::M)
	{
		GameManager::GetSoundManager()->ToggleMute();
	}
	//Hitting the key for "1" will turn off two player mode
	else if (k == sf::Keyboard::Num1)
	{
		GameManager::SetOnePlayerMode();
	}
	//Hitting the key for "2" will turn on two player mode
	else if (k == sf::Keyboard::Num2)
	{
		GameManager::SetTwoPlayerMode();
	}
}