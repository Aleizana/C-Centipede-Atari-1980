#ifndef _ScorpionMoveBaseState
#define _ScorpionMoveBaseState

#include "TEAL\CommonElements.h"

class Scorpion;
class ScorpionMoveRightState;
class ScorpionMoveLeftState;

class ScorpionMoveBaseState
{
public:
	ScorpionMoveBaseState() = default;
	ScorpionMoveBaseState(const ScorpionMoveBaseState&) = delete;
	ScorpionMoveBaseState& operator=(const ScorpionMoveBaseState&) = delete;
	virtual ~ScorpionMoveBaseState() = default;

	virtual const ScorpionMoveBaseState* SwapToOtherState() const = 0;
	virtual const float GetSpriteDirFromState() const = 0;
	virtual void HandleScorpionMove(Scorpion* scorpToRef, int& countMovement, int leftPrevCellCheck) const = 0;

	static const ScorpionMoveLeftState MoveLeftState;
	static const ScorpionMoveRightState MoveRightState;

protected:



};

#endif