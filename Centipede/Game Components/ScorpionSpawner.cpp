// ScorpionSpawner
// Andre Berthiaume, March 2013

#include "ScorpionSpawner.h"
#include "ScorpionFactory.h"
#include "Scorpion.h"
#include "Grid.h"
#include "ScorpionMover.h"
#include "GridManager.h"
#include "ScorpionMoveBaseState.h"
#include "GameManager.h"

ScorpionSpawner::ScorpionSpawner()
	: myPixelOffset(GameManager::GetGridMgr()->GetPixelDistance() / GameManager::GetGridMgr()->GetPixelDistanceOffset()), ColSpawnVal_LeftDir(GameManager::GetGridMgr()->GetNumCols()),
		setColSpawnVal(0), scorpionPresent(false), spawnerAlarmNumTimer(0.0f), pHoldScorpState(nullptr)
{
}

void ScorpionSpawner::Alarm1()
{
	//The alarm will only execute if true
	if (scorpionPresent)
	{
		//Randomly select and set the direction of the new scorpion
		ChooseRandDir();

		ScorpionFactory::CreateScorpion(sf::Vector2f((float)(GameManager::GetGridMgr()->GetPixelDistance() * setColSpawnVal) + myPixelOffset,
			(float)((GameManager::GetGridMgr()->GetPixelDistance() * rowSpawnVal) - myPixelOffset)),
			rowSpawnVal, setColSpawnVal,
			pHoldScorpState);

		//Set alarm zero to activate this object in 5 seconds
		SetAlarm(spawnerAlarmNum, spawnerAlarmNumTimer);
	}
	
}
void ScorpionSpawner::Destroy()
{
	//delete scorpionMoverRef;
}

void ScorpionSpawner::ChooseRandDir()
{
	//Randomly select a direction for the scorpion to spawn in and subsequently face
	if (rand() % randDirectionRange % randDirectionDivisor == RandDirTarget)
	{
		setColSpawnVal = ColSpawnVal_LeftDir;
		pHoldScorpState = (ScorpionMoveBaseState*)&ScorpionMoveBaseState::MoveLeftState;
	}
	else
	{
		setColSpawnVal = ColSpawnVal_RightDir;
		pHoldScorpState = (ScorpionMoveBaseState*)&ScorpionMoveBaseState::MoveRightState;
	}
}

void ScorpionSpawner::SetScorpSpawnParams(bool scorpPresent, float scorpSpawnRate, float scorpSpeed)
{
	scorpionPresent = scorpPresent;
	spawnerAlarmNumTimer = scorpSpawnRate;

	//Set the factory's speed value
	ScorpionFactory::SetScorpionSpeed(scorpSpeed);

	if (scorpPresent)
	{
		//Set alarm zero to activate this object in 5 seconds
		SetAlarm(spawnerAlarmNum, spawnerAlarmNumTimer);
	}
	
}