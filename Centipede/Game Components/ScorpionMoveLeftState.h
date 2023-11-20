#ifndef _ScorpionMoveLeftState
#define _ScorpionMoveLeftState

#include "ScorpionMoveBaseState.h"
#include "TEAL/CommonElements.h"

class ScorpionMoveLeftState : public ScorpionMoveBaseState
{

public:
	ScorpionMoveLeftState() = default;
	ScorpionMoveLeftState(const ScorpionMoveLeftState&) = delete;
	ScorpionMoveLeftState& operator=(const ScorpionMoveLeftState&) = delete;
	virtual ~ScorpionMoveLeftState() = default;

	virtual const ScorpionMoveBaseState* SwapToOtherState() const override;
	virtual const float GetSpriteDirFromState() const override;
	virtual void HandleScorpionMove(Scorpion* scorpToRef, int& countMovement, int leftPrevCellCheck) const override;

private:
	const float SpriteDirectionScalar = 1.0f;
};

#endif