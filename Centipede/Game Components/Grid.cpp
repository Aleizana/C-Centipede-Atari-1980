#include "Grid.h"
#include "GridManager.h"
#include "MushroomFactory.h"
#include "Mushroom.h"
#include <stack>
#include "GameManager.h"

GameGrid::GameGrid()
	: numRows(0), numCols(0), rowStartingNum(0), colStartingNum(0), pixelDistance(0)
{
}

void GameGrid::SetGridSize(int setRows, int setCols, int setCellSize, int rowStartIndex, int colStartIndex)
{
	//32
	numRows = setRows;

	//1
	rowStartingNum = rowStartIndex;

	//30
	numCols = setCols;

	//0
	colStartingNum = colStartIndex;

	//Determines screen resolution
	//16x16
	pixelDistance = setCellSize;

	//Create vector based on num rows x num cols to track items on the grid, init to all spaces open (nullptr)
	gridMap.assign(setRows * setCols, nullptr);
}

GameGrid::CheckGridResult GameGrid::CheckGridSpot(int row, int col)
{
	//col < Instance().colStartingNum, unneeded check
	//Does not accept any indices outside of the range of the grid
	if (row < rowStartingNum || col >= numCols || col < colStartingNum)
	{
		//Tell the caller that the position they asked for is either the walls or is beyond the walls of the grid
		return GameGrid::WALL;
	}
	//The grid will notify that this is the bottom of the window
	else if (row > numRows)
	{
		return GameGrid::BOTTOM_WINDOW;
	}

	//Gets the index in the gridMap from the row and col numbers
	int index = CalculateIndex(row, col);

	//Check to see if the grid position is open
	if (gridMap[index] == nullptr)
	{
		//Return notice that the grid position is open
		return GameGrid::OPEN;
	}
	else
	{
		//if the object at the index (mushrom) is poisoned, return this information
		if (gridMap[index]->GetLifeState() == GameObject::POISON)
		{
			return GameGrid::POISONED;
		}
		else
		{
			//Space is taken, tell the caller that it is unavailable by returning SPOT_TAKEN
			return GameGrid::SPOT_TAKEN;
		}
		
	}
}

GameGrid::CheckGridResult GameGrid::CheckGridSpot(int row, int col, int &indexRef)
{
	//col < Instance().colStartingNum, unneeded check
	//Does not accept any indices outside of the range of the grid
	if (row < rowStartingNum || col >= numCols || col < colStartingNum)
	{
		//Tell the caller that the position they asked for is either the walls or is beyond the walls of the grid
		return GameGrid::WALL;
	}
	//The grid will notify that this is the bottom of the window
	else if (row > numRows)
	{
		return GameGrid::BOTTOM_WINDOW;
	}

	//Gets the index in the gridMap from the row and col numbers
	indexRef = CalculateIndex(row, col);

	//Check to see if the grid position is open
	if (gridMap[indexRef] == nullptr)
	{
		//Return notice that the grid position is open
		return GameGrid::OPEN;
	}
	else
	{
		//Space is taken, tell the spawner that it is unavailable by returning SPOT_TAKEN
		return GameGrid::SPOT_TAKEN;
	}
}

void GameGrid::PassGameObjectRef(int row, int col, GameObject* objRef)
{
	//Gets the index in the gridMap from the row and col numbers
	int index = CalculateIndex(row, col);

	gridMap[index] = objRef;
}

std::stack<Mushroom*> GameGrid::GenerateMushroomRegenStack_Score()
{
	std::stack<Mushroom*> dmgStack;

	for (int gridIter = gridStartingIndex; gridIter < (int)gridMap.size(); gridIter++)
	{
		if (gridMap.at(gridIter) != nullptr && gridMap.at(gridIter)->GetObjectType() == GameObject::ObjectType::MUSHROOM)
		{
			if (gridMap.at(gridIter)->GetMyHealth() < gridMap.at(gridIter)->GetStartingHP())
			{
				ConsoleMsg::WriteLine("Mushroom regenerated");

				//Send score command for mushroom regeneration
				MushroomFactory::SendMushRegenScoreCommand();

				dmgStack.push((Mushroom*)gridMap.at(gridIter));
			}
			else if (gridMap.at(gridIter)->GetLifeState() == GameObject::POISON)
			{
				//Reset the mushroom to be alive and have it's sprite offset reset from showing the poisoned sprite
				static_cast<Mushroom*>(gridMap.at(gridIter))->ResetState();
			}
		}
	}

	return dmgStack;
}

void GameGrid::ResetGrid()
{
	//Create vector based on num rows x num cols to track items on the grid, init to all spaces open (nullptr)
	gridMap.assign(numRows * numCols, nullptr);
}



GameObject* GameGrid::GetGridObjectByIndex(int index)
{
	return gridMap[index];
}

void GameGrid::ClearGridSpot(int row, int col)
{
	//Does not accept any indices outside of the range of the grid
	if (row <= rowStartingNum || row > numRows || col < colStartingNum || col >= numCols)
	{
		return;
	}

	//Gets the index in the gridMap from the row and col numbers
	int index = CalculateIndex(row, col);

	//Set the position in the grid to be "open"
	gridMap[index] = nullptr;
}

int GameGrid::CalculateIndex(int row, int col)
{
	//Calculation need for both col = 0 and col > 0
	//Gets the index for the leftmost positions in the grid
	int index = (row - rowStartingNum) * numCols;

	if (index <= 0)
	{
		index = col;
	}
	//Special calculation for when the col > 0, gets the horizontal pos
	else if (col > colStartingNum)
	{
		index += col;
	}

	return index;
}

void GameGrid::StoreGridData()
{
	//Create a local reference to an array with indices equal to the number of dimensions in the grid
	std::vector<int> holdRowCol;

	//Iterate through the cells of the grid
	for (GameObject* gridObject : gridMap)
	{
		//If an object exists in that cell, store it's index
		if (gridObject != nullptr && gridObject->GetObjectType() != GameObject::ObjectType::GLYPH)
		{
			//Fill the vector with the row and column of the current mushroom
			holdRowCol.push_back(gridObject->GetMyRow());
			holdRowCol.push_back(gridObject->GetMyCol());

			//Add the row/col array to the queue of mushroom pos
			storeGridObjectIndices.push(holdRowCol);

			holdRowCol.clear();
		}
	}

	//Reset the grid vector to nullptr given that all of it's references will be destroyed
	gridMap.assign(numRows * numCols, nullptr);
}

void GameGrid::RestoreGridData()
{
	//Create a local reference to an array with indices equal to the number of dimensions in the grid
	std::vector<int> holdRowCol;

	int holdRow;
	int holdCol;

	//Iterate through the list of stored row/col positions and create a mushroom in that grid pos until there are none left in the queue
	while (!storeGridObjectIndices.empty())
	{
		holdRowCol = storeGridObjectIndices.front();
		holdRow = holdRowCol.at(gridObjectArrFirstIndex);
		holdCol = holdRowCol.at(gridObjectArrSecondIndex);
		MushroomFactory::CreateMushroom(holdRow, holdCol);
		storeGridObjectIndices.pop();
	}
}