#ifndef _FleaMover
#define _FleaMover

#include "TEAL\CommonElements.h"

//Reference to the flea will be used in many functions
class Flea;

class FleaMover
{
public:
	FleaMover();
	FleaMover& operator=(const FleaMover&) = delete;
	FleaMover(FleaMover& _copyBlaster) = delete;
	~FleaMover() = default;

	//Function that centipede head will call when it needs to be moved across the screen
	void HandleFleaMove(Flea* fleaToMove, int& countMovement, int leftPrevCellCheck);

	//Once the flea takes damage, it's speed will be multiplied by the mover
	void HandleFleaDamage(Flea* fleaToMove);

	float GetBaseFleaSpeed();

private:
	//Flea game properties
	const float FleaSpeed = 4.0f;
	const float FleaSpeedMult = 1.5f;

	//The number of frames between which the flea will randomly decide to spawn a mushroom
	const int numFramesToCheckMushSpawn = 2;

	//For modulo on randomly generated value by the flea to spawn a mushroom, is essentially the chance to spawn a mushroom out of the chanceToSpawnMushroomNumRange
	const int chanceToSpawnMushroomDivisor = 1;
	const int chanceToSpawnMushroomNumRange = 6;

	//The amount of rows that the flea moves through when leaving a cell
	const int rowIncrementor = 1;

	//Store speed in it's own variable so that it can be multiplied upon taking damage
	float fleaCurrSpeed;

	//For storing the cell size from the grid
	int leftPrevCellCheck;

	//Query the mushroom spawner and spawn mushroom in flea position if pos is unused
	//Returns a boolean so that the flea mover can have the result
	bool CallMushroomSpawner(Flea* fleaToMove);
};

#endif