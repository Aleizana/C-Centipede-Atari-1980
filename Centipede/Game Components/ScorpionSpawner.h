// ScorpionSpawner
// Andre Berthiaume, March 2013

#ifndef _ScorpionSpawner
#define _ScorpionSpawner

#include "TEAL\CommonElements.h"

//Needed for reference to scorpion direction, no risk of include loop as scorpion factory does not include 
#include "ScorpionFactory.h"

class Scorpion;
class ScorpionMoveBaseState;

class ScorpionSpawner : public GameObject
{
public:
	ScorpionSpawner();
	ScorpionSpawner(const ScorpionSpawner&) = delete;
	ScorpionSpawner& operator=(const ScorpionSpawner&) = delete;
	~ScorpionSpawner() = default;

	//For spawning scorpions periodically 
	virtual void Alarm1();

	virtual void Destroy();

	//For the wave to set the parameters of the scorpion spawner
	void SetScorpSpawnParams(bool scorpPresent, float scorpSpawnRate, float scorpSpeed);

private:
	//Get the size of a cell so that the scorpion spawner can know where scorpions need to be spawned
	int myPixelOffset;

	//Arbitrary spawn point for testing scorpion spawn, the direction will be randomly selected upon spawn
	const int ColSpawnVal_RightDir = 0;

	//Will be set in the constructor to be at the last grid col
	int ColSpawnVal_LeftDir;

	//The spawn value that will be randomly set in ChooseRandDir()
	int setColSpawnVal;

	bool scorpionPresent;

	//Arbitrary spawn point for testing scorpion spawn
	const int rowSpawnVal = 7;

	//For setting the alarm number and timer of spawning scorpions, arbitrary number for now just to test spawn 
	const int spawnerAlarmNum = 1;
	float spawnerAlarmNumTimer;

	//Range of values from 0 - val that will be randomly generated
	const int randDirectionRange = 4;
	//Will modulo the val from the range to determine if it is divisible by this number and will choose a direction based upon that
	const int randDirectionDivisor = 2;

	//Modulo target for the random selection
	const int RandDirTarget = 0;

	ScorpionMoveBaseState* pHoldScorpState;

	//Function that randomly selects a direction and sets the direction accordingly
	void ChooseRandDir();
};

#endif _ScorpionSpawner