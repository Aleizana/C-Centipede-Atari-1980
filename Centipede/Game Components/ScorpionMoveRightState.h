#ifndef _ScorpionMoveRightState
#define _ScorpionMoveRightState

#include "ScorpionMoveBaseState.h"
#include "TEAL/CommonElements.h"

class ScorpionMoveRightState : public ScorpionMoveBaseState
{

public:
	ScorpionMoveRightState() = default;
	ScorpionMoveRightState(const ScorpionMoveRightState&) = delete;
	ScorpionMoveRightState& operator=(const ScorpionMoveRightState&) = delete;
	virtual ~ScorpionMoveRightState() = default;

	virtual const ScorpionMoveBaseState* SwapToOtherState() const override;
	virtual const float GetSpriteDirFromState() const override;
	virtual void HandleScorpionMove(Scorpion* scorpToRef, int& countMovement, int leftPrevCellCheck) const override;

private:
	const float SpriteDirectionScalar = -1.0f;
};

#endif