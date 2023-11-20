#ifndef _SpiderMoveStateBase
#define _SpiderMoveStateBase

//Included for the single calculation of the spider's bottom-of-screen limit
//Given that this is an abstract class, there is no cpp file to calculate this from. Thus, the include is necessary
#include "GridManager.h"
#include "TEAL/WindowManager.h"

struct SpiderOffsetArray;
class Spider;

class SpiderMoveState
{
public:
	const SpiderOffsetArray* GetMoveOffsets() const { return MyMoveOffsets; }
	virtual const SpiderMoveState* GetNextState(Spider* cSpider) const = 0;
	virtual const bool HandleOffScreenCheck(float spiderXPos) const = 0;
	virtual const float HandleMovementLimitCheck(float spiderYPos, float moveYOffset) const = 0;

	virtual void Show() const = 0;

protected:
	SpiderMoveState() = default;
	SpiderMoveState(const SpiderMoveState&) = delete;				// Prevent copy-construction
	SpiderMoveState& operator=(const SpiderMoveState&) = delete;	// Prevent assignment
	~SpiderMoveState() = default;											// Only this class can delete

	const SpiderOffsetArray* MyMoveOffsets = nullptr;

	//Random range and target values for each of the states to be randomly decided
	const int randValRange = 4;

	const float StopYMovement = 0.0f;
};

#endif 