#ifndef _SpawnMgr
#define _SpawnMgr

#include "TEAL\CommonElements.h"

class FleaSpawner;
class ControllerManager;
class ScorpionSpawner;
class SpiderSpawner;

class SpawnerManager
{
public:
	SpawnerManager();
	SpawnerManager(const SpawnerManager& otherMgr) = delete;
	SpawnerManager& operator=(SpawnerManager&) = delete;
	~SpawnerManager() = default;

	//For the spawner manager to create new instances of each of the spawners at the start of every scene
	void InitSpawners();

	FleaSpawner* GetFleaSpawner();
	ScorpionSpawner* GetScorpSpawner();
	SpiderSpawner* GetSpiderSpawner();


private:
	//Pointers to hold refs to each of the spawners in the game
	FleaSpawner* fleaSpawnRef;
	ScorpionSpawner* scorpSpawnRef;
	SpiderSpawner* spiderSpawnRef;
};

#endif