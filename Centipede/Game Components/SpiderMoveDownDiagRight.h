#ifndef _SpiderMoveDownDiagRight
#define _SpiderMoveDownDiagRight

#include "SpiderMoveState.h"

class SpiderMoveDownDiagRight : public SpiderMoveState
{
public:
	SpiderMoveDownDiagRight();
	SpiderMoveDownDiagRight(const SpiderMoveDownDiagRight& copyMe) = delete;
	SpiderMoveDownDiagRight& operator=(const SpiderMoveDownDiagRight&) = delete;
	~SpiderMoveDownDiagRight() = default;

	virtual const SpiderMoveState* GetNextState(Spider* cSpider) const override;
	virtual void Show() const override;
	virtual const bool HandleOffScreenCheck(float spiderXPos) const override;
	virtual const float HandleMovementLimitCheck(float spiderYPos, float moveYOffset) const;

private:
	//Random range and target values for each of the states to be randomly decided
	const int RightDirArrOffset = 2;
};

#endif