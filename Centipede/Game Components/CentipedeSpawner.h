#ifndef _CentiSpawner
#define _CentiSpawner

#include "TEAL\CommonElements.h"

class CentipedeHead;
class CentipedeHeadMover;

static const float X_Spawn = 240.0f;
static const float Y_Spawn = 0.0f;

class CentipedeSpawner
{
public:
	CentipedeSpawner();
	CentipedeSpawner(const CentipedeSpawner& copyMgr) = delete;
	CentipedeSpawner& operator=(const CentipedeSpawner) = delete;
	~CentipedeSpawner();

	//Function for the spawner to create the centipede at the beginning of a level
	void LevelStartSpawn();

private:
	//Vector for storing references to all of the centipede heads in the scene
	std::vector<CentipedeHead*> headRefs;

	//Reference to the head mover that the spawner will own and pass onto centipede heads
	CentipedeHeadMover* headMoverRef;

	//Variables to hold the pixel position in which the head will initially spawn
	float headSpawn_X;
	float headSpawn_Y;

	//Offset based on the cell size / dimensions of the grid
	float spawnGridOffset;
};

#endif