#ifndef _Grid
#define _Grid

#include <vector>
#include <queue>
#include "TEAL\CommonElements.h"
#include <array>
#include <stack>

#include "GridManager.h"
//#include "Mushroom.h"

class Mushroom;

class GameGrid
{
public:
	GameGrid();
	GameGrid(GameGrid& copyGrid) = delete;
	GameGrid& operator=(GameGrid&) = delete;
	~GameGrid() = default;

	//Enum to allow for specification of the result of an object checking if it can spawn/move in the grid
	enum CheckGridResult { WALL, SPOT_TAKEN, OPEN, BOTTOM_WINDOW, POISONED};

	//For the level to set the grid parameters upon start-up
	void SetGridSize(int setRows, int setCols, int setCellSize, int rowStartIndex, int colStartIndex);

	//Tells the grid to store the positions of the mushrooms currently alive for level switching
	void StoreGridData();

	//Tells the grid to use the stored index list to re-fill its cells
	void RestoreGridData();

	//Verifies if a grid position is open based on row and col index, returns boolean
	CheckGridResult CheckGridSpot(int row, int col);

	//Verifies if a grid position is open based on row and col index, returns boolean and stores the index into the call-by-reference variable
	CheckGridResult CheckGridSpot(int row, int col, int &indexRef);

	//Returns the GameObject at the index requested, or return nullptr if nothing is there
	GameObject* GetGridObjectByIndex(int index);

	//Frees up a position in the grid given a row and col index
	void ClearGridSpot(int row, int col);

	//GameObject spawner passes a reference to their spawned object to the grid so that it can have a reference to what is there
	void PassGameObjectRef(int row, int col, GameObject* objRef);

	std::stack<Mushroom*> GenerateMushroomRegenStack_Score();

	void ResetGrid();
	

private:
	//Number of rows and columns within the grid
	int numRows;
	int numCols;

	//Indices where the columns and rows start, needed for calculating the index from the vector
	int rowStartingNum;
	int colStartingNum;

	//Size of a single cell within the grid
	//The distance refers to the pixels it takes to get from one end to the other end of a cell
	int pixelDistance;

	//GameObject pointer vector to store the game object in a given position on the grid
	std::vector<GameObject*> gridMap;

	//For accessing the arrays of the grid object queue
	const int gridObjectArrFirstIndex = 0;
	const int gridObjectArrSecondIndex = 1;

	//Saves the indices of the grid to restore the mushrooms when the owning player comes back into play
	//Every index stores 2 values, one for the row and one for the column, or equal to the number of dimensions in the grid thus the usage of pixel distance offset
	std::queue<std::vector<int>> storeGridObjectIndices;

	//Takes input of a row and column index and converts it into an index in the gridMap array
	int CalculateIndex(int row, int col);

	//To pinpoint the index for the start of the grid
	const int gridStartingIndex = 0;

	
};

#endif