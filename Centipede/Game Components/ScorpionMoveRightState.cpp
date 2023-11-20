#include "ScorpionMoveRightState.h"
#include "Scorpion.h"
#include "ScorpionMover.h"

const ScorpionMoveBaseState* ScorpionMoveRightState::SwapToOtherState() const
{
	return nullptr;
}

const float ScorpionMoveRightState::GetSpriteDirFromState() const
{
	return SpriteDirectionScalar;
}

void ScorpionMoveRightState::HandleScorpionMove(Scorpion* scorpToRef, int& countMovement, int leftPrevCellCheck) const
{
	scorpToRef->GetMyMover()->HandleScorpionMove_Right(scorpToRef, countMovement, leftPrevCellCheck);
}
