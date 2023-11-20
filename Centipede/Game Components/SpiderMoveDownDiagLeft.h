#ifndef _SpiderMoveDownDiagLeft
#define _SpiderMoveDownDiagLeft

#include "SpiderMoveState.h"

class Spider;

class SpiderMoveDownDiagLeft : public SpiderMoveState
{
public:
	SpiderMoveDownDiagLeft();
	SpiderMoveDownDiagLeft(const SpiderMoveDownDiagLeft& copyMe) = delete;
	SpiderMoveDownDiagLeft& operator=(const SpiderMoveDownDiagLeft&) = delete;
	~SpiderMoveDownDiagLeft() = default;

	virtual const SpiderMoveState* GetNextState(Spider* cSpider) const override;
	virtual void Show() const override;
	virtual const bool HandleOffScreenCheck(float spiderXPos) const override;
	virtual const float HandleMovementLimitCheck(float spiderYPos, float moveYOffset) const;

private:
};

#endif