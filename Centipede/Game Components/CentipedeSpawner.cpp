#include "CentipedeSpawner.h"
#include "CentipedeHead.h"
#include "CentipedeHeadMover.h"
#include "Grid.h"

CentipedeSpawner::CentipedeSpawner()
{
	//Create the mover class for the centipede head
	headMoverRef = new CentipedeHeadMover;

	//Offset to add to the x and y of the pos of a centipede obj so that they can start within the middle of a cell
	spawnGridOffset = (float)(GameGrid::Instance().GetPixelDistance() / GameGrid::Instance().GetPixelDistanceOffset());

	//Create the first centipede in the level to start the game
	LevelStartSpawn();
}

CentipedeSpawner::~CentipedeSpawner()
{
	delete headMoverRef;
}

void CentipedeSpawner::LevelStartSpawn()
{
	//Get the row and column of the centipede head by dividing their pixel pos by the cell size of the grid
	//Casting is safe given that the X and Y pixel position in which the head will spawn must be divisible by the whole number cell size
	int headCol = (int)X_Spawn / GameGrid::GetPixelDistance();
	int headRow = (int)Y_Spawn / GameGrid::GetPixelDistance();

	//Initialize the spawn position of the head of the centipede at the beginning of a level, with offset based on the cell size / dimensions of the grid
	headSpawn_X = X_Spawn + spawnGridOffset;
	headSpawn_Y = Y_Spawn - spawnGridOffset;
	//headSpawn_X = X_Spawn;
	//headSpawn_Y = Y_Spawn;

	//Holds the x and y spawn pos plus the offset of the centipede head
	sf::Vector2f headSpawnPos = sf::Vector2f(headSpawn_X, headSpawn_Y);

	//Create a new centipede head and add it to the vector of heads
	headRefs.push_back(new CentipedeHead(headSpawnPos, headRow, headCol, headMoverRef));
}