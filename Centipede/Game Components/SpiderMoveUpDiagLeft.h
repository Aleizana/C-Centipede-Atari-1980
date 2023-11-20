#ifndef _SpiderMoveUpDiagLeft
#define _SpiderMoveUpDiagLeft

#include "SpiderMoveState.h"

class SpiderMoveUpDiagLeft : public SpiderMoveState
{
public:
	SpiderMoveUpDiagLeft();
	SpiderMoveUpDiagLeft(const SpiderMoveUpDiagLeft& copyMe) = delete;
	SpiderMoveUpDiagLeft& operator=(const SpiderMoveUpDiagLeft&) = delete;
	~SpiderMoveUpDiagLeft() = default;

	virtual const SpiderMoveState* GetNextState(Spider* cSpider) const override;
	virtual void Show() const override;
	virtual const bool HandleOffScreenCheck(float spiderXPos) const override;
	virtual const float HandleMovementLimitCheck(float spiderYPos, float moveYOffset) const;

private:
};

#endif