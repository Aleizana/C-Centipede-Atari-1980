#include "CmdScoreByValue.h"
#include <iostream>
#include "ScoreManager.h"
#include "GameManager.h"

CmdScoreValue::CmdScoreValue(int val)
	: points(val)
{
	printf("Score Command created: Points = %i\n", val);
}

void CmdScoreValue::Execute()
{
	printf("\tScore Command Executing\n");
	GameManager::GetScoreMgr()->AddScore(points);
}
