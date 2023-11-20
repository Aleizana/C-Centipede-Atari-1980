#ifndef _GridMgr
#define _GridMgr

#include <vector>

//To be able to store the active Grid
class GameGrid;

class GridManager
{
private:
	//Vector to store each of the active Grids
	std::vector<GameGrid*> gridList;

	//Initialize constants for the properties of the grid
	static const int numRows = 32;
	static const int rowStartIndex = 1;
	static const int numCols = 30;
	static const int colStartIndex = 0;
	static const int cellSize = 16;

	//Variable for offsetting the pixel position of an object so that it can be in the middle of a cell
	//By dividing the cell size by 2 and adding that to a pixel position, you place an object in the middle of a cell
	static const int pixelDistanceOffset = 2;

public:
	GridManager() = default;												// Private constructor
	GridManager(const GridManager&) = delete;				// Prevent copy-construction
	GridManager& operator=(const GridManager&) = delete;	// Prevent assignment
	~GridManager();											// Only this class can delete

	//Getters for numRows and numCols and their starting indices
	int GetNumRows();
	int GetNumCols();
	int GetRowStartIndex();
	int GetColStartIndex();
	int GetPixelDistance();
	int GetPixelDistanceOffset();

	GameGrid* CreateGrid();

	
};

#endif
