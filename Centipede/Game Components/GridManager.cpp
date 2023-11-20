#include "GridManager.h"
#include "Grid.h"
#include "TEAL/CommonElements.h"

GridManager::~GridManager()
{
	//Delete each of the Grids from the game
	for (GameGrid* grid : gridList)
	{
		delete grid;
	}
}

int GridManager::GetNumRows()
{
	return numRows;
}

int GridManager::GetNumCols()
{
	return numCols;
}

int GridManager::GetRowStartIndex()
{
	return rowStartIndex;
}

int GridManager::GetColStartIndex()
{
	return colStartIndex;
}

int GridManager::GetPixelDistance()
{
	return cellSize;
}

int GridManager::GetPixelDistanceOffset()
{
	return pixelDistanceOffset;
}

GameGrid* GridManager::CreateGrid()
{
	ConsoleMsg::WriteLine("Created a new Grid.");

	//Create a new Grid and add it to the back of the vector
	GameGrid* newGrid = new GameGrid;
	gridList.push_back(newGrid);

	newGrid->SetGridSize(numRows, numCols, cellSize, rowStartIndex, colStartIndex);

	return newGrid;
}