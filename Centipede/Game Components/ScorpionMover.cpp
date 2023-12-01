#include "ScorpionMover.h"
#include "Scorpion.h"
#include <math.h>
#include "GridManager.h"
#include "ScorpionFactory.h"
#include "GameManager.h"
#include "PlayerManager.h"
#include "Player.h"
#include "Grid.h"
#include "Mushroom.h"

ScorpionMover::ScorpionMover()
	: scorpionSpeed(0.0f)
{
}

void ScorpionMover::HandleScorpionMove_Left(Scorpion* scorpionToMove, int& countMovement, int leftPrevCellCheck)
{
	//Get the current position of the Scorpion
	sf::Vector2f scorpionNewPos = scorpionToMove->GetMyPos();

	//Update the y-value of the Scorpion by it's speed
	scorpionNewPos.x -= scorpionSpeed;

	//Update the position of the Scorpion with the added y-val
	scorpionToMove->SetMyPos(scorpionNewPos);

	//Increment the number of frames that the Scorpion has moved, no risk of integer getting too large due to the nature of the Scorpion being destroyed off-screen
	countMovement++;

	//If the Scorpion has moved enough to have left it's previous cell, update it's pos
	if (countMovement == leftPrevCellCheck / (int)scorpionSpeed)
	{
		int newCol = scorpionToMove->GetMyCol() - ScorpGridMoveVal;

		//Increment the cols traveled by the Scorpion
		scorpionToMove->SetMyCol(newCol);

		//For storing the index of the grid object
		int indexRef;

		//Check the grid and if there is a mushroom at the scorpion's position, poison it
		if (GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->CheckGridSpot(scorpionToMove->GetMyRow(), newCol, indexRef) == GameGrid::CheckGridResult::SPOT_TAKEN)
		{
			//Get the grid object using the index stored as a reference variable in the grid check previously
			GameObject* holdObj = (GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->GetGridObjectByIndex(indexRef));

			//Check if the object is a mushroom
			if (holdObj->GetObjectType() == GameObject::MUSHROOM)
			{
				//Now that we know the object is a mushroom, activate it's poisoned state
				static_cast<Mushroom*>(holdObj)->ActivatePoisonState();
			}
		}

		//Reset the move check
		countMovement = 0;

		//Now that it has left it's previous cell, check if the scorpion is off the left side of the screen
		HandleOffScreenCheck_Left(scorpionToMove, scorpionNewPos);
	}


	

}

void ScorpionMover::HandleScorpionMove_Right(Scorpion* scorpionToMove, int& countMovement, int leftPrevCellCheck)
{
	//Get the current position of the Scorpion
	sf::Vector2f scorpionNewPos = scorpionToMove->GetMyPos();

	//Update the y-value of the Scorpion by it's speed
	scorpionNewPos.x += scorpionSpeed;

	//Update the position of the Scorpion with the added y-val
	scorpionToMove->SetMyPos(scorpionNewPos);

	//Increment the number of frames that the Scorpion has moved, no risk of integer getting too large due to the nature of the Scorpion being destroyed off-screen
	countMovement++;

	//If the Scorpion has moved enough to have left it's previous cell, update it's pos
	if (countMovement == leftPrevCellCheck / (int)scorpionSpeed)
	{
		int newCol = scorpionToMove->GetMyCol() + ScorpGridMoveVal;

		//Increment the cols traveled by the Scorpion
		scorpionToMove->SetMyCol(newCol);

		//For storing the index of the grid object
		int indexRef;

		//Check the grid and if there is a mushroom at the scorpion's position, poison it
		if (GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->CheckGridSpot(scorpionToMove->GetMyRow(), newCol, indexRef) == GameGrid::CheckGridResult::SPOT_TAKEN)
		{
			//Get the grid object using the index stored as a reference variable in the grid check previously
			GameObject* holdObj = (GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->GetGridObjectByIndex(indexRef));

			//Check if the object is a mushroom
			if (holdObj->GetObjectType() == GameObject::MUSHROOM)
			{
				//Now that we know the object is a mushroom, activate it's poisoned state
				static_cast<Mushroom*>(holdObj)->ActivatePoisonState();
			}
		}

		//Reset the move check
		countMovement = 0;

		//Now that it has left it's previous cell, check if the scorpion is off the right side of the screen
		HandleOffScreenCheck_Right(scorpionToMove, scorpionNewPos);

	}

	

}

void ScorpionMover::SetScorpionSpeed(float speed)
{
	scorpionSpeed = speed;
}

bool ScorpionMover::HandleOffScreenCheck_Left(Scorpion* scorpionToMove, sf::Vector2f newPos)
{
	//If the Scorpion crosses the left-of-screen threshold, destroy it
	if (newPos.x < 0)
	{
		HandleScorpionDestroy(scorpionToMove);

		//If the scorpion is to be destroyed, let the main move function know
		return true;
	}

	//If the scorpion wont be destroyed
	return false;
}

bool ScorpionMover::HandleOffScreenCheck_Right(Scorpion* scorpionToMove, sf::Vector2f newPos)
{
	//If the Scorpion crosses the right-of-screen threshold, destroy it
	if (newPos.x > WindowManager::Window().getSize().x)
	{
		HandleScorpionDestroy(scorpionToMove);

		//If the scorpion is to be destroyed, let the main move function know
		return true;
	}

	//If the scorpion wont be destroyed
	return false;
}

void ScorpionMover::HandleScorpionDestroy(Scorpion* scorpionToMove)
{
	ConsoleMsg::WriteLine("Scorpion went off screen and will be destroyed");

	//Tell TEAL to destroy the Scorpion
	scorpionToMove->MarkForDestroy();

	ScorpionFactory::DecrementScorpionCount();

	ScorpionFactory::StopScorpionLoop();

	//Set the state of the Scorpion to dead
	scorpionToMove->SetLifeState(GameObject::DEAD);
}