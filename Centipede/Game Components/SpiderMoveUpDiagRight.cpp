#include "SpiderMoveUpDiagRight.h"
#include <iostream>
#include "SpiderMoveCollection.h"
#include <assert.h>
#include "SpiderMover.h"
#include "Grid.h"
#include "MoveFSM.h"
#include "SpiderFactory.h"
#include "PlayerManager.h"
#include "GameManager.h"

SpiderMoveUpDiagRight::SpiderMoveUpDiagRight()
{
	std::cout << "Initializing SpiderMoveUpDiagRight state\n";

	MyMoveOffsets = SpiderMoveCollection::OffsetsUpDiagonalRight;
}
void SpiderMoveUpDiagRight::Show() const
{
	std::cout << "SpiderMoveUpDiagRight";
}

const bool SpiderMoveUpDiagRight::HandleOffScreenCheck(float spiderXPos) const
{
	//Return whether the xPos of the spider is at the cutoff point
	return spiderXPos > GameManager::GetRightScreenCutoff();
}

const float SpiderMoveUpDiagRight::HandleMovementLimitCheck(float spiderYPos, float moveYOffset) const
{
	//If the spider would exceed the player area limit, set the y-offset to 0 so that it can't go through them. Else, return the offset to move by
	return (spiderYPos + moveYOffset < GameManager::GetPlayerMgr()->GetPlayerAreaLimit()) ? StopYMovement : moveYOffset;
}

const SpiderMoveState* SpiderMoveUpDiagRight::GetNextState(Spider* cSpider) const
{
	const SpiderMoveState* pNextState = nullptr;

	//Calculate a number based on the rand val range
	int randValHold = rand() % randValRange + randValOffset;

	pNextState = SpiderFactory::GetSpiderStateByIndex(randValHold);
		

	return pNextState;
}