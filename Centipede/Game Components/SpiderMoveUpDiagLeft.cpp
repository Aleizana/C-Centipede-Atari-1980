#include "SpiderMoveUpDiagLeft.h"
#include <iostream>
#include "SpiderMoveCollection.h"
#include <assert.h>
#include "SpiderMover.h"
#include "Grid.h"
#include "MoveFSM.h"
#include "SpiderFactory.h"
#include "PlayerManager.h"
#include "GameManager.h"

SpiderMoveUpDiagLeft::SpiderMoveUpDiagLeft()
{
	std::cout << "Initializing SpiderMoveUpDiagLeft state\n";

	MyMoveOffsets = SpiderMoveCollection::OffsetsUpDiagonalLeft;
}
void SpiderMoveUpDiagLeft::Show() const
{
	std::cout << "SpiderMoveUpDiagLeft";
}

const bool SpiderMoveUpDiagLeft::HandleOffScreenCheck(float spiderXPos) const
{
	//Return whether the xPos of the spider is at the left cutoff point
	return spiderXPos < GameManager::GetLeftScreenCutoff();
}

const float SpiderMoveUpDiagLeft::HandleMovementLimitCheck(float spiderYPos, float moveYOffset) const
{
	//If the spider would exceed the player area limit, set the y-offset to 0 so that it can't go through them. Else, return the offset to move by
	return (spiderYPos + moveYOffset < GameManager::GetPlayerMgr()->GetPlayerAreaLimit()) ? StopYMovement : moveYOffset;
}

const SpiderMoveState* SpiderMoveUpDiagLeft::GetNextState(Spider* cSpider) const
{
	const SpiderMoveState* pNextState = nullptr;

	//Calculate a number based on the rand val range
	int randValHold = rand() % randValRange;

	pNextState = SpiderFactory::GetSpiderStateByIndex(randValHold);

	return pNextState;
}