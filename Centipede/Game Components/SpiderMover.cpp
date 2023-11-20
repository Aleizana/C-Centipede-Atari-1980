#include "SpiderMover.h"
#include "MoveFSM.h"
#include "Grid.h"
#include "Spider.h"
#include "SpiderMoveState.h"
#include "SpiderMoveCollection.h"
#include <math.h>
#include <assert.h>
#include "GridManager.h"
#include "PlayerManager.h"

SpiderMover::SpiderMover()
{

	holdSpeed = 0;
}

void SpiderMover::HandleSpiderMove(Spider* spiderToMove, int& moveArrIncrementor)
{
	//Get the current position of the Spider
	sf::Vector2f SpiderNewPos = spiderToMove->GetMyPos();

	const SpiderMoveState* holdState = spiderToMove->GetMyState();

	float holdX = holdState->GetMoveOffsets()[moveArrIncrementor].GetColOffset() * holdSpeed;
	float holdY = holdState->GetMoveOffsets()[moveArrIncrementor].GetRowOffset() * holdSpeed;

	SpiderNewPos.x += holdX;

	//float holdNewYPos = SpiderNewPos.y + holdY;

	//If the spider would exceed the player area limit or the bottom of the screen, set the y-offset to 0 so that it can't go through them. Else, this will be the same value.
	holdY = holdState->HandleMovementLimitCheck(SpiderNewPos.y, holdY);

	SpiderNewPos.y += holdY;

	//if the spider exceeds the left or right screen limits, mark it for destroy
	if (holdState->HandleOffScreenCheck(SpiderNewPos.x))
	{
		spiderToMove->SetLifeState(GameObject::LifeState::DEAD);
		spiderToMove->MarkForDestroy();
	}
	else
	{
		//Update the position of the Spider with the added y-val
		spiderToMove->SetMyPos(SpiderNewPos);

		//Increment offset index
		moveArrIncrementor++;

		//if the movement array has been finished, get the next random movement
		if (moveArrIncrementor >= SpiderMoveCollection::arrMax)
		{
			spiderToMove->GetNextState();
			moveArrIncrementor = 0;
		}
	}
	

}

void SpiderMover::SetSpiderSpeed(float speed)
{
	holdSpeed = speed;
}
