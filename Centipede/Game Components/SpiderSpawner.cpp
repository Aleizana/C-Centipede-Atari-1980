// SpiderSpawner
// Andre Berthiaume, March 2013

#include "SpiderSpawner.h"
#include "Spider.h"
#include "Grid.h"
#include "SpiderMover.h"
#include "SpiderFactory.h"
#include "GridManager.h"
#include "GameManager.h"

SpiderSpawner::SpiderSpawner() : 
	myPixelOffset(GameManager::GetGridMgr()->GetPixelDistance() / GameManager::GetGridMgr()->GetPixelDistanceOffset()), //Get the size of a cell so that the Spider spawner can know where Spiders need to be spawned
	colSpawnValLeft(GameManager::GetGridMgr()->GetNumCols()),
	spiderPresent(false),
	spiderSpawnRate(0.0f)
{

}

void SpiderSpawner::Alarm2()
{
	//The alarm will only act while spiderPresent is true
	if (spiderPresent)
	{
		int holdRand = (rand() % randValRange) % randValDivisor;

		//If the number is equal to the target, choose left direction and tell spider factory to spawn with that dir
		if (holdRand == randValTarget)
		{
			SpiderFactory::CreateSpider(sf::Vector2f((float)(GameManager::GetGridMgr()->GetPixelDistance() * colSpawnValLeft) + myPixelOffset,
				(float)((GameManager::GetGridMgr()->GetPixelDistance() * rowSpawnVal) - myPixelOffset)), rowSpawnVal, colSpawnValLeft, SpiderFactory::SpiderMainDirection::LEFT);

		}
		//Else choose right direction and tell spider factory to spawn with that dir
		else
		{
			SpiderFactory::CreateSpider(sf::Vector2f((float)(GameManager::GetGridMgr()->GetPixelDistance() * colSpawnValRight) + myPixelOffset,
				(float)((GameManager::GetGridMgr()->GetPixelDistance() * rowSpawnVal) - myPixelOffset)), rowSpawnVal, colSpawnValRight, SpiderFactory::SpiderMainDirection::RIGHT);
		}



		//Set alarm zero to activate this object in 5 seconds
		SetAlarm(spawnerAlarmNum, spiderSpawnRate);
	}
	
}
void SpiderSpawner::Destroy()
{

}

void SpiderSpawner::SetSpiderSpawnParams(bool _spiderPresent, float spawnRate, float speed)
{
	spiderSpawnRate = spawnRate;
	spiderPresent = _spiderPresent;

	if (spiderPresent)
	{
		SetAlarm(spawnerAlarmNum, spiderSpawnRate);
	}
	

	//Update the speed stored in the spider factory
	SpiderFactory::SetSpiderSpeed(speed);
}