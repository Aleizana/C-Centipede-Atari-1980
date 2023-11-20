#ifndef _CentiHeadMover
#define _CentiHeadMover

#include "TEAL\CommonElements.h"

//Forward declare of centipede head
class CentipedeHead;

class CentipedeHeadMover
{
public:
	CentipedeHeadMover();
	CentipedeHeadMover(const CentipedeHeadMover& copyMgr) = delete;
	CentipedeHeadMover& operator=(const CentipedeHeadMover) = delete;
	~CentipedeHeadMover() = default;

	//Function that centipede head will call when it needs to be moved across the screen
	void HandleCentiHeadMove(CentipedeHead* headToMove);

	void InitCentipedeHeadMover();

private:
	//Function to determine the direction of the centipede's initial movement as set it's initial movement path
	void SpawnMovement(CentipedeHead* headToMove);

	//Handles the checking of the grid for the head mover along with deciding the appropriate direction based upon the result
	void HandleGridCheck(CentipedeHead* headToMove);

	void HandleMove_NoGridCheck(CentipedeHead* headToMove);

	//Move the head of the centipede down the screen
	void MoveDown(CentipedeHead* headToMove);

	//Move the head of the centipede left on the screen
	void MoveLeft(CentipedeHead* headToMove);

	//Move the head of the centipede right on the screen
	void MoveRight(CentipedeHead* headToMove);

	//Move the head of the centipede up the screen
	void MoveUp(CentipedeHead* headToMove);

	//Function that will check if the player area is ahead of the centipede when it is moving up
	bool CheckForPlrArea(CentipedeHead* headToMove);

	//For setting cardinal and directional movement to their respective horizontal direction
	//Highly repeated code
	void SetLeftDirection(CentipedeHead* headToMove);
	void SetRightDirection(CentipedeHead* headToMove);

	//Function to handle setting the row or column number once the centipede head has left it's previous cell
	void SetHeadRowCol(CentipedeHead* headToMove);

	//For determining the random movement during the centipede's second movement pattern
	const int RandSpawnMoveRange = 1;
	const int RandSpawnMoveTarget = 0;

	//Speed of the centipede head
	const float HeadSpeed = 2.0f;

	//Minimum clamp for the centipede head when it's not in the player zone
	const float headMinClamp_Y_MainMove = 0;

	//Val to determine how many cells away the centipede will check in the grid
	const int GridCheckDistance = 1;

	//Val to increment the number of columns the centipede moves in a singular direction up/down
	const int ColIncrement = 1;

	//Val to increment the number of columns the centipede moves in a singular direction left/right
	const int RowIncrement = 1;

	//For the holding and changing of the position of a centipede head
	sf::Vector2f headPosHold;

	//Counter for the centipede's movement to track how many pixels it has moved and know when it has left its previous cell
	int countMovement;

	//Number to know when the centipede has left it's previous cell, will be initialized by dividing the cell size of the grid by the speed of the centipede
	float leftPrevCellCheck;


};



#endif
