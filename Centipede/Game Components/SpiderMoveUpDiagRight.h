#ifndef _SpiderMoveUpDiagRight
#define _SpiderMoveUpDiagRight

#include "SpiderMoveState.h"

class Spider;

class SpiderMoveUpDiagRight : public SpiderMoveState
{
public:
	SpiderMoveUpDiagRight();
	SpiderMoveUpDiagRight(const SpiderMoveUpDiagRight& copyMe) = delete;
	SpiderMoveUpDiagRight& operator=(const SpiderMoveUpDiagRight&) = delete;
	~SpiderMoveUpDiagRight() = default;

	virtual const SpiderMoveState* GetNextState(Spider* cSpider) const override;
	virtual void Show() const override;
	virtual const bool HandleOffScreenCheck(float spiderXPos) const override;
	virtual const float HandleMovementLimitCheck(float spiderYPos, float moveYOffset) const;

private:
	//Random range and target values for each of the states to be randomly decided
	const int randValOffset = 2;
};

#endif