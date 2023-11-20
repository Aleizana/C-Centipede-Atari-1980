#include "SpiderMoveDown.h"
#include <iostream>
#include "SpiderMoveCollection.h"
#include <assert.h>
#include "SpiderMover.h"
#include "Grid.h"
#include "MoveFSM.h"
#include "SpiderFactory.h"
#include "GameManager.h"
#include "Spider.h"

SpiderMoveDown::SpiderMoveDown()
{
	std::cout << "Initializing SpiderMoveDown state\n";

	MyMoveOffsets = SpiderMoveCollection::OffsetsDown;
}
void SpiderMoveDown::Show() const
{
	std::cout << "SpiderMoveDown";
}

const bool SpiderMoveDown::HandleOffScreenCheck(float spiderXPos) const
{
	//Spider can not go off screen in this state
	return false;
}

const float SpiderMoveDown::HandleMovementLimitCheck(float spiderYPos, float moveYOffset) const
{
	//If the spider would exceed the bottom of screen limit, set the y-offset to 0 so that it can't go through them. Else, return the offset to move by
	return (spiderYPos + moveYOffset > GameManager::GetBottomOfScreenLimit()) ? StopYMovement : moveYOffset;
}

const SpiderMoveState* SpiderMoveDown::GetNextState(Spider* cSpider) const
{
	const SpiderMoveState* pNextState = nullptr;

	//To hold the random index chosen for the spider's direction
	int randValHold = 0;

	//Up and down will not be tested for initially, so that the spider can walk onto the screen
	//Test for the left move state values specifically
	if (cSpider->GetSpiderDir() == SpiderFactory::SpiderMainDirection::LEFT)
	{
		randValHold = rand() % randValRange;

		//if (randValHold == randTargetDownDiagLeft)
		//{
		//	pNextState = (SpiderMoveState*)&MoveFSM::StateSpiderMoveDownDiagLeft;
		//}
		//else if (randValHold == randTargetUpDiagLeft)
		//{
		//	pNextState = (SpiderMoveState*)&MoveFSM::StateSpiderMoveUpDiagLeft;
		//}
	}
	//Test for the right move state values specifically
	else if (cSpider->GetSpiderDir() == SpiderFactory::SpiderMainDirection::RIGHT)
	{
		randValHold = rand() % randValRange + RightDirArrOffset;

		//if (randValHold == randTargetDownDiagRight)
		//{
		//	pNextState = (SpiderMoveState*)&MoveFSM::StateSpiderMoveDownDiagRight;
		//}
		//else if (randValHold == randTargetUpDiagRight)
		//{
		//	pNextState = (SpiderMoveState*)&MoveFSM::StateSpiderMoveUpDiagRight;
		//}
	}
	else
	{
		assert(false && "Invalid direction");
	}

	pNextState = SpiderFactory::GetSpiderStateByIndex(randValHold);
	
	////Test separately for up and down
	//if (randValHold == randTargetDown)
	//{
	//	pNextState = (SpiderMoveState*)&MoveFSM::StateSpiderMoveDown;
	//}
	//else if (randValHold == randTargetUp)
	//{
	//	pNextState = (SpiderMoveState*)&MoveFSM::StateSpiderMoveUp;
	//}

	return pNextState;
}