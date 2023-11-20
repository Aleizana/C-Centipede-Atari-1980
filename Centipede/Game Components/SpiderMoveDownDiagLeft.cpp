#include "SpiderMoveDownDiagLeft.h"
#include <iostream>
#include "SpiderMoveCollection.h"
#include <assert.h>
#include "SpiderMover.h"
#include "Grid.h"
#include "MoveFSM.h"
#include "SpiderFactory.h"
#include "GameManager.h"

SpiderMoveDownDiagLeft::SpiderMoveDownDiagLeft()
{
	std::cout << "Initializing SpiderMoveDownDiagLeft state\n";

	MyMoveOffsets = SpiderMoveCollection::OffsetsDownDiagonalLeft;
}
void SpiderMoveDownDiagLeft::Show() const
{
	std::cout << "SpiderMoveDownDiagLeft";
}

const bool SpiderMoveDownDiagLeft::HandleOffScreenCheck(float spiderXPos) const
{
	//Return whether the spider has gone off the left side of the screen
	return spiderXPos < GameManager::GetLeftScreenCutoff();
}

const float SpiderMoveDownDiagLeft::HandleMovementLimitCheck(float spiderYPos, float moveYOffset) const
{
	//If the spider would exceed the bottom of screen limit, set the y-offset to 0 so that it can't go through them. Else, return the offset to move by
	return (spiderYPos + moveYOffset > GameManager::GetBottomOfScreenLimit()) ? StopYMovement : moveYOffset;
}

const SpiderMoveState* SpiderMoveDownDiagLeft::GetNextState(Spider* cSpider) const
{
	const SpiderMoveState* pNextState = nullptr;

	//Calculate a number based on the rand val range
	int randValHold = rand() % randValRange;

	pNextState = SpiderFactory::GetSpiderStateByIndex(randValHold);

	return pNextState;
}