#include "SpawnerManager.h"
#include "FleaSpawner.h"
#include "ScorpionSpawner.h"
#include "SpiderSpawner.h"

SpawnerManager::SpawnerManager() : fleaSpawnRef(nullptr), scorpSpawnRef(nullptr), spiderSpawnRef(nullptr)
{
}

FleaSpawner* SpawnerManager::GetFleaSpawner()
{
	return fleaSpawnRef;
}

ScorpionSpawner* SpawnerManager::GetScorpSpawner()
{
	return scorpSpawnRef;
}

SpiderSpawner* SpawnerManager::GetSpiderSpawner()
{
	return spiderSpawnRef;
}

void SpawnerManager::InitSpawners()
{
	//Create the flea spawner
	fleaSpawnRef = new FleaSpawner();

	//Create a scorpion spawner
	scorpSpawnRef = new ScorpionSpawner;

	//Create a spider spawner
	spiderSpawnRef = new SpiderSpawner;
}

