#include "SpiderMoveUp.h"
#include <iostream>
#include "SpiderMoveCollection.h"
#include <assert.h>
#include "SpiderMover.h"
#include "Grid.h"
#include "MoveFSM.h"
#include "SpiderFactory.h"
#include "PlayerManager.h"
#include "GameManager.h"
#include "Spider.h"

SpiderMoveUp::SpiderMoveUp()
{
	std::cout << "Initializing SpiderMoveUp state\n";

	MyMoveOffsets = SpiderMoveCollection::OffsetsUp;
}
void SpiderMoveUp::Show() const
{
	std::cout << "SpiderMoveUp";
}

const bool SpiderMoveUp::HandleOffScreenCheck(float spiderXPos) const
{
	//The spider is only moving up in this state, so it can not go off screen due to the player area limit check
	return false;
}

const float SpiderMoveUp::HandleMovementLimitCheck(float spiderYPos, float moveYOffset) const
{
	//If the spider would exceed the player area limit, set the y-offset to 0 so that it can't go through them. Else, return the offset to move by
	return (spiderYPos + moveYOffset < GameManager::GetPlayerMgr()->GetPlayerAreaLimit()) ? StopYMovement : moveYOffset;
}

const SpiderMoveState* SpiderMoveUp::GetNextState(Spider* cSpider) const
{
	const SpiderMoveState* pNextState = nullptr;

	//To hold the random index chosen for the spider's direction
	int randValHold = 0;

	//Up and down will not be tested for initially, so that the spider can walk onto the screen
	//Test for the left move state values specifically
	if (cSpider->GetSpiderDir() == SpiderFactory::SpiderMainDirection::LEFT)
	{
		randValHold = rand() % randValRange;
	}
	//Test for the right move state values specifically
	else if (cSpider->GetSpiderDir() == SpiderFactory::SpiderMainDirection::RIGHT)
	{
		randValHold = rand() % randValRange + RightDirArrOffset;
	}
	else
	{
		assert(false && "Invalid direction");
	}

	pNextState = SpiderFactory::GetSpiderStateByIndex(randValHold);

	return pNextState;
}