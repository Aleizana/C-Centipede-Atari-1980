// FleaSpawner
// Andre Berthiaume, March 2013

#include "FleaSpawner.h"
#include "Flea.h"
#include "FleaMover.h"
#include "FleaFactory.h"
#include "GridManager.h"
#include "MushroomFactory.h"
#include "GameManager.h"

FleaSpawner::FleaSpawner() :
	myPixelOffset(GameManager::GetGridMgr()->GetPixelDistance() / GameManager::GetGridMgr()->GetPixelDistanceOffset()), //Get the size of a cell so that the flea spawner can know where fleas need to be spawned
	atNumMushToSpawn(0),
	fleaPresent(false)
{
	
}

void FleaSpawner::Alarm0()
{
	//The alarm will only act while fleaPresent is true
	if (fleaPresent)
	{
		int holdMushCount = MushroomFactory::GetMushCount();

		//If the low-limit of mushrooms has been met, spawn a flea
		if (holdMushCount <= atNumMushToSpawn)
		{
			FleaFactory::CreateFlea(sf::Vector2f((float)(GameManager::GetGridMgr()->GetPixelDistance() * colSpawnVal) + myPixelOffset,
				(float)((GameManager::GetGridMgr()->GetPixelDistance() * rowSpawnVal) - myPixelOffset)), rowSpawnVal, colSpawnVal);
		}

		//Set alarm zero to activate and check the mushroom count again in 5 seconds
		SetAlarm(spawnerAlarmNum, spawnerAlarmNumTimer);
	}

}
void FleaSpawner::Destroy()
{

}

void FleaSpawner::SetFleaSpawnParams(bool _fleaPresent, int numMushToSpawn, int chanceToTriggerMushSpawn)
{
	atNumMushToSpawn = numMushToSpawn;
	fleaPresent = _fleaPresent;

	FleaFactory::SetFleaChanceToTriggerMushSpawn(chanceToTriggerMushSpawn);

	if (_fleaPresent)
	{
		SetAlarm(spawnerAlarmNum, spawnerAlarmNumTimer);
	}

	
}