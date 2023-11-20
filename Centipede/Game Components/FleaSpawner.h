// FleaSpawner
// Andre Berthiaume, March 2013

#ifndef _FleaSpawner
#define _FleaSpawner

#include "TEAL\CommonElements.h"

class MushroomSpawner;
class FleaMover;

class FleaSpawner : public GameObject
{
public:
	FleaSpawner();
	FleaSpawner(const FleaSpawner&) = delete;
	FleaSpawner& operator=(const FleaSpawner&) = delete;
	~FleaSpawner() = default;

	//For spawning fleas periodically 
	virtual void Alarm0();

	virtual void Destroy();

	//For the wave to set the parameters of the flea spawner
	void SetFleaSpawnParams(bool fleaPresent, int numMushToSpawn, int chanceToTriggerSpawn);

private:

	//Get the size of a cell so that the flea spawner can know where fleas need to be spawned
	int myPixelOffset;

	//Arbitrary spawn point for testing flea spawn
	const int colSpawnVal = 10;

	//y = 0 is always the top of the screen where the flea will always spawn
	const int rowSpawnVal = 0;

	//For setting the alarm number and timer of spawning fleas, arbitrary number for now just to test spawn 
	const int spawnerAlarmNum = 0;
	const float spawnerAlarmNumTimer = 5.0f;

	//The number of mushrooms that need to be present/less-than this number to spawn a flea
	int atNumMushToSpawn;
	
	//Boolean to determine if fleas will be spawned
	bool fleaPresent;

};

#endif _FleaSpawner