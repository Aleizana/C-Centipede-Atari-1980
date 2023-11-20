#include "FleaMover.h"
#include "Grid.h"
#include "MushroomFactory.h"
#include "Flea.h"
#include <math.h>
#include "GridManager.h"
#include "GameManager.h"
#include "FleaFactory.h"

FleaMover::FleaMover() : 
	fleaCurrSpeed(FleaSpeed)
{

}

void FleaMover::HandleFleaMove(Flea* fleaToMove, int& countMovement, int leftPrevCellCheck)
{
	//Get the current position of the flea
	sf::Vector2f fleaNewPos = fleaToMove->GetMyPos();

	//Update the y-value of the flea by it's speed
	fleaNewPos.y += fleaToMove->GetSpeed();

	//Update the position of the flea with the added y-val
	fleaToMove->SetMyPos(fleaNewPos);

	//Increment the number of frames that the flea has moved, no risk of integer getting too large due to the nature of the flea being destroyed off-screen
	countMovement++;

	//If the flea crosses the bottom-of-screen threshold, destroy it
	if (fleaNewPos.y > WindowManager::Window().getSize().y)
	{
		ConsoleMsg::WriteLine("Flea went off screen and will be destroyed");

		//Tell TEAL to destroy the flea
		fleaToMove->MarkForDestroy();

		//Set the state of the flea to dead
		fleaToMove->SetLifeState(GameObject::DEAD);
	}
	//If the flea has moved enough to have left it's previous cell, perform a random check to spawn a mushroom
	else if (countMovement == leftPrevCellCheck / FleaSpeed)
	{
		int newRow = fleaToMove->GetMyRow() + rowIncrementor;

		//Increment the rows traveled by the flea
		fleaToMove->SetMyRow(newRow);

		//Reset the move check
		countMovement = 0;

		//If the flea's health is full, initiate a random check to see if it will spawn a mushroom
		if (fleaToMove->GetMyHealth() == fleaToMove->FleaSpawnHealth)
		{
			int randTest = rand() % FleaFactory::GetFleaChanceToTriggerMushSpawn();

			//Rand() will return a number between 0 and chanceToSpawnMushroomNumRange, and the chance to spawn a mushroom will if the number is equal to the divisor
			if (randTest == chanceToSpawnMushroomDivisor)
			{
				//Function to call the mushroom spawner
				CallMushroomSpawner(fleaToMove);
			}
		}

	}
	
}

bool FleaMover::CallMushroomSpawner(Flea* fleaToMove)
{
	if (MushroomFactory::CreateMushroom(fleaToMove->GetMyRow(), fleaToMove->GetMyCol()))
	{
		ConsoleMsg::WriteLine("Flea mover spawned mushroom");
		return true;
	}
	
	//If the mushroom failed to spawn, return false
	ConsoleMsg::WriteLine("Flea mover couldn't spawn mushroom");
	return false;
}

void FleaMover::HandleFleaDamage(Flea* fleaToMove)
{
	//Increase the flea's speed by a multiplier
	fleaToMove->SetSpeedThroughMulitplier(FleaSpeedMult);
}

float FleaMover::GetBaseFleaSpeed()
{
	return FleaSpeed;
}
