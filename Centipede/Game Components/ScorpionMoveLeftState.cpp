#include "ScorpionMoveLeftState.h"
#include "Scorpion.h"
#include "ScorpionMover.h"

const ScorpionMoveBaseState* ScorpionMoveLeftState::SwapToOtherState() const
{
	return nullptr;
}

const float ScorpionMoveLeftState::GetSpriteDirFromState() const
{
	return SpriteDirectionScalar;
}

void ScorpionMoveLeftState::HandleScorpionMove(Scorpion* scorpToRef, int& countMovement, int leftPrevCellCheck) const
{
	scorpToRef->GetMyMover()->HandleScorpionMove_Left(scorpToRef, countMovement, leftPrevCellCheck);
}
