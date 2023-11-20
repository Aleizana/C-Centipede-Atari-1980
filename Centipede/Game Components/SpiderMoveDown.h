#ifndef _SpiderMoveDown
#define _SpiderMoveDown

#include "SpiderMoveState.h"

class SpiderMoveDown : public SpiderMoveState
{
public:
	SpiderMoveDown();
	SpiderMoveDown(const SpiderMoveDown& copyMe) = delete;
	SpiderMoveDown& operator=(const SpiderMoveDown&) = delete;
	~SpiderMoveDown() = default;

	virtual const SpiderMoveState* GetNextState(Spider* cSpider) const override;
	virtual void Show() const override;
	virtual const bool HandleOffScreenCheck(float spiderXPos) const override;
	virtual const float HandleMovementLimitCheck(float spiderYPos, float moveYOffset) const;

private:
	//Random range and target values for each of the states to be randomly decided
	const int RightDirArrOffset = 2;
};

#endif