#ifndef _SpiderMoveUp
#define _SpiderMoveUp

#include "SpiderMoveState.h"

class Spider;

class SpiderMoveUp : public SpiderMoveState
{
public:
	SpiderMoveUp();
	SpiderMoveUp(const SpiderMoveUp& copyMe) = delete;
	SpiderMoveUp& operator=(const SpiderMoveUp&) = delete;
	~SpiderMoveUp() = default;

	virtual const SpiderMoveState* GetNextState(Spider* cSpider) const override;
	virtual void Show() const override;
	virtual const bool HandleOffScreenCheck(float spiderXPos) const override;
	virtual const float HandleMovementLimitCheck(float spiderYPos, float moveYOffset) const;

private:
	//Random range and target values for each of the states to be randomly decided
	const int RightDirArrOffset = 2;

	
};

#endif