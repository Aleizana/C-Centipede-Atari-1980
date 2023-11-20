// SpiderSpawner
// Andre Berthiaume, March 2013

#ifndef _SpiderSpawner
#define _SpiderSpawner

#include "TEAL\CommonElements.h"

class MushroomSpawner;
class SpiderMover;

class SpiderSpawner : public GameObject
{
public:
	SpiderSpawner();
	SpiderSpawner(const SpiderSpawner&) = delete;
	SpiderSpawner& operator=(const SpiderSpawner&) = delete;
	~SpiderSpawner() = default;

	//For spawning Spiders periodically 
	virtual void Alarm2();

	virtual void Destroy();

	void SetSpiderSpawnParams(bool _spiderPresent, float spawnRate, float speed);

private:

	//Get the size of a cell so that the Spider spawner can know where Spiders need to be spawned
	int myPixelOffset;

	//Arbitrary spawn point for testing Spider spawn
	const int colSpawnValRight = 0;

	const int colSpawnValLeft;

	//y = 0 is always the top of the screen where the Spider will always spawn
	const int rowSpawnVal = 25;

	//For setting the alarm number and timer of spawning Spiders
	const int spawnerAlarmNum = 2;

	//For determining the random horizontal direction of the spider initially
	const int randValRange = 5;
	const int randValDivisor = 2;

	//Target number for left dir
	const int randValTarget = 0;

	//Values from the wave file
	bool spiderPresent;
	float spiderSpawnRate;



};

#endif _SpiderSpawner