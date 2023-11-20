#include "SpiderMoveDownDiagRight.h"
#include <iostream>
#include "SpiderMoveCollection.h"
#include <assert.h>
#include "SpiderMover.h"
#include "Grid.h"
#include "MoveFSM.h"
#include "SpiderFactory.h"
#include "GameManager.h"

SpiderMoveDownDiagRight::SpiderMoveDownDiagRight()
{
	std::cout << "Initializing SpiderMoveDownDiagRight state\n";

	MyMoveOffsets = SpiderMoveCollection::OffsetsDownDiagonalRight;
}
void SpiderMoveDownDiagRight::Show() const
{
	std::cout << "SpiderMoveDownDiagRight";
}

const bool SpiderMoveDownDiagRight::HandleOffScreenCheck(float spiderXPos) const
{
	//Return whether the spider has gone off the right side of the screen
	return spiderXPos > GameManager::GetRightScreenCutoff();
}

const float SpiderMoveDownDiagRight::HandleMovementLimitCheck(float spiderYPos, float moveYOffset) const
{
	//If the spider would exceed the bottom of screen limit, set the y-offset to 0 so that it can't go through them. Else, return the offset to move by
	return (spiderYPos + moveYOffset > GameManager::GetBottomOfScreenLimit()) ? StopYMovement : moveYOffset;
}

const SpiderMoveState* SpiderMoveDownDiagRight::GetNextState(Spider* cSpider) const
{
	const SpiderMoveState* pNextState = nullptr;

	//Calculate a number based on the rand val range
	int randValHold = rand() % randValRange + RightDirArrOffset;

	pNextState = SpiderFactory::GetSpiderStateByIndex(randValHold);


	return pNextState;
}