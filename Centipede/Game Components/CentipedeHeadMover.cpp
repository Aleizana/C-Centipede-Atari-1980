#include "CentipedeHeadMover.h"
#include "CentipedeHead.h"
#include "Level1.h"
#include "Grid.h"

CentipedeHeadMover::CentipedeHeadMover()
{
	//The centipede will not have moved yet at the beginning of the level, so init to 0
	countMovement = 0;

	//Target num for count movement so that headmover can know when the head has left it's previous cell
	//Val is based on the cell size / speed of the head
	leftPrevCellCheck = GameGrid::Instance().GetPixelDistance() / HeadSpeed;
}

void CentipedeHeadMover::InitCentipedeHeadMover()
{
	//The centipede will not have moved yet at the beginning of the level, so init to 0
	countMovement = 0;
}

void CentipedeHeadMover::HandleCentiHeadMove(CentipedeHead* headToMove)
{
	//Increment the the number of frames in which the centipede has moved at the beginning of the frame
	countMovement++;

	if (headToMove->GetMyMovePattern() == CentipedeHead::MovePattern::FIRST_MOVE || headToMove->GetMyMovePattern() == CentipedeHead::MovePattern::SECOND_MOVE)
	{
		//Function that handles the first and second move patterns, along with setting the movement pattern to the next phase after
		SpawnMovement(headToMove);
	}
	//The second move pattern will generate a random direction between left and right and allow the main_move pattern to check the grid
	else if (headToMove->GetMyMovePattern() == CentipedeHead::MovePattern::MAIN_MOVE || headToMove->GetMyMovePattern() == CentipedeHead::MovePattern::PLR_ZONE)
	{
		//headToMove->SetMinClampY(headMinClamp_Y_MainMove);
		
		//If the centipede has not left the previous cell yet, do not query grid and continue in the set cardinal direction
		if (countMovement != leftPrevCellCheck)
		{
			//Handle movement without querying the grid
			HandleMove_NoGridCheck(headToMove);
		}
		else
		{
			//Update the row/col of the centipede head now that it has moved out of its previous cell
			SetHeadRowCol(headToMove);

			//If the movement direction was sequential, switch to an individual cardinal direction
			if (headToMove->GetMyMoveDir() == CentipedeHead::DOWN_END_LEFT || headToMove->GetMyMoveDir() == CentipedeHead::UP_END_LEFT)
			{
				SetLeftDirection(headToMove);
			}
			else if (headToMove->GetMyMoveDir() == CentipedeHead::DOWN_END_RIGHT || headToMove->GetMyMoveDir() == CentipedeHead::UP_END_RIGHT)
			{
				SetRightDirection(headToMove);
			}

			//Query the grid before making the next movement
			HandleGridCheck(headToMove);
			
		}
	}
	
	//If the centipede has moved enough to have left it's previous grid cell, allow the mover to check the path for a wall/mushroom
	if (countMovement == (int)leftPrevCellCheck)
	{
		//Reset the counter to avoid very large ints being stored
		countMovement = 0;
	}
}

void CentipedeHeadMover::SpawnMovement(CentipedeHead* headToMove)
{
	if (headToMove->GetMyMovePattern() == CentipedeHead::FIRST_MOVE)
	{
		//Set the current direction of the centipede to be moving down
		headToMove->SetMyMoveCardinal(CentipedeHead::MoveCardinal::DOWN);

		if (countMovement != leftPrevCellCheck)
		{
			//Move the head downwards as it spawns
			MoveDown(headToMove);
		}
		else
		{
			//Increment the row number of the centipede by 1 given that it moved down a cell
			headToMove->SetHeadRow(headToMove->GetHeadRow() + RowIncrement);

			//Set the movement pattern to be in it's second phase
			headToMove->SetMyMovePattern(CentipedeHead::MovePattern::SECOND_MOVE);
		}
	}
	
	//The first move pattern will enable the secnd move pattern once the head has left it's previous cell, which will then allow the main move pattern to start checking the grid
	if (headToMove->GetMyMovePattern() == CentipedeHead::MovePattern::SECOND_MOVE)
	{
		//Calculate the next direction between left and right randomly between 0 and the pre-set high range
		int holdRand = rand() % RandSpawnMoveRange;

		//Move the centipede left or right initially based on randomized chance
		if (holdRand == RandSpawnMoveTarget)
		{
			//Set cardinal and directional states to be in one direction
			SetLeftDirection(headToMove);
		}
		else
		{
			//Set cardinal and directional states to be in one direction
			SetRightDirection(headToMove);
		}
		
		//Set the centipede to be in it's main pattern until it reaches the bottom of the screen
		headToMove->SetMyMovePattern(CentipedeHead::MovePattern::MAIN_MOVE);

		//Call the grid check function to handle initial movement between left/right in this frame
		HandleGridCheck(headToMove);
	}
}

void CentipedeHeadMover::SetHeadRowCol(CentipedeHead* headToMove)
{
	if (headToMove->GetMyMoveCardinal() == CentipedeHead::MoveCardinal::DOWN)
	{
		//Increment the row number of the centipede by 1 given that it moved down a cell
		headToMove->SetHeadRow(headToMove->GetHeadRow() + RowIncrement);
	}
	else if (headToMove->GetMyMoveCardinal() == CentipedeHead::MoveCardinal::UP)
	{
		//Increment the row number of the centipede by -1 given that it moved up a cell
		headToMove->SetHeadRow(headToMove->GetHeadRow() - RowIncrement);
	}
	else if (headToMove->GetMyMoveCardinal() == CentipedeHead::MoveCardinal::LEFT)
	{
		//Increment the col number of the centipede by -1 given that it moved left a cell
		headToMove->SetHeadCol(headToMove->GetHeadCol() - ColIncrement);
	}
	else if (headToMove->GetMyMoveCardinal() == CentipedeHead::MoveCardinal::RIGHT)
	{
		//Increment the col number of the centipede by 1 given that it moved right a cell
		headToMove->SetHeadCol(headToMove->GetHeadCol() + ColIncrement);
	}
}

void CentipedeHeadMover::MoveDown(CentipedeHead* headToMove)
{
	//Receive the current position of the centipede head
	headPosHold = headToMove->GetHeadPos();

	//Move the centipede head down based on the speed
	headPosHold.y += HeadSpeed;

	//Set the pos of the head object to match the newly set pos
	headToMove->SetHeadPos(headPosHold);
}

void CentipedeHeadMover::MoveUp(CentipedeHead* headToMove)
{
	//Receive the current position of the centipede head
	headPosHold = headToMove->GetHeadPos();

	//Move the centipede head up based on the speed
	headPosHold.y -= HeadSpeed;

	//Set the pos of the head object to match the newly set pos
	headToMove->SetHeadPos(headPosHold);
}

void CentipedeHeadMover::MoveLeft(CentipedeHead* headToMove)
{
	//Receive the current position of the centipede head
	headPosHold = headToMove->GetHeadPos();

	//Move the centipede head left based on the speed
	headPosHold.x -= HeadSpeed;

	//Set the pos of the head object to match the newly set pos
	headToMove->SetHeadPos(headPosHold);
}

void CentipedeHeadMover::MoveRight(CentipedeHead* headToMove)
{
	//Receive the current position of the centipede head
	headPosHold = headToMove->GetHeadPos();

	//Move the centipede head left based on the speed
	headPosHold.x += HeadSpeed;

	//Set the pos of the head object to match the newly set pos
	headToMove->SetHeadPos(headPosHold);
}

bool CentipedeHeadMover::CheckForPlrArea(CentipedeHead* headToMove)
{
	//Check if centipede head will be moving into the player area limit and return true if so
	//The player area limit is offset by the same value that the centipede head pos is offset at spawn
	if (headToMove->GetHeadPos().y < Level1::playerAreaLimit - (GameGrid::Instance().GetPixelDistance() / GameGrid::Instance().GetPixelDistanceOffset()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CentipedeHeadMover::HandleGridCheck(CentipedeHead* headToMove)
{
	//For storing the result of a query of the grid
	GameGrid::CheckGridResult holdResult;

	switch (headToMove->GetMyMoveDir())
	{
	case CentipedeHead::LEFT_BOUND:
		//Check the position in the grid at col - 1, which is where the head would end up
		holdResult = GameGrid::CheckGridSpot(headToMove->GetHeadRow(), headToMove->GetHeadCol() - GridCheckDistance);
		
		//if there is nothing occupying the space
		if (holdResult == GameGrid::CheckGridResult::OPEN)
		{
			//Move the centipede head left
			MoveLeft(headToMove);
		}
		else if (holdResult == GameGrid::SPOT_TAKEN || holdResult == GameGrid::WALL)
		{
			//If the centipede head is in the player zone pattern, it will choose up instead of down
			if (headToMove->GetMyMovePattern() == CentipedeHead::PLR_ZONE)
			{
				//Set the centipede to move up and finish by moving right
				headToMove->SetMyMoveDir(CentipedeHead::UP_END_RIGHT);

				//Recursively call HandleGridCheck to find correct movement pos
				HandleGridCheck(headToMove);
			}
			//== CentipedeHead::MAIN_MOVE
			else
			{
				//Set the centipede to move down and finish by moving right
				headToMove->SetMyMoveDir(CentipedeHead::DOWN_END_RIGHT);

				//Recursively call HandleGridCheck to find correct movement pos
				HandleGridCheck(headToMove);
			}

			
		}

		break;
	case CentipedeHead::RIGHT_BOUND:
		//Check the position in the grid at col + 1, which is where the head would end up
		holdResult = GameGrid::CheckGridSpot(headToMove->GetHeadRow(), headToMove->GetHeadCol() + GridCheckDistance);

		//if there is nothing occupying the space
		if (holdResult == GameGrid::CheckGridResult::OPEN)
		{
			//Move the centipede head right
			MoveRight(headToMove);
		}
		else if (holdResult == GameGrid::CheckGridResult::SPOT_TAKEN || holdResult == GameGrid::CheckGridResult::WALL)
		{
			//If the centipede head is in the player zone pattern, it will choose up instead of down
			if (headToMove->GetMyMovePattern() == CentipedeHead::MovePattern::PLR_ZONE)
			{
				//Set the centipede to move up and finish by moving right
				headToMove->SetMyMoveDir(CentipedeHead::UP_END_LEFT);

				//Recursively call HandleGridCheck to find correct movement pos
				HandleGridCheck(headToMove);
			}
			//== CentipedeHead::MAIN_MOVE
			else
			{
				//Set the centipede to move down and finish by moving left
				headToMove->SetMyMoveDir(CentipedeHead::DOWN_END_LEFT);

				//Recursively call HandleGridCheck to find correct movement pos
				HandleGridCheck(headToMove);
			}

			
		}

		break;
	case CentipedeHead::DOWN_END_LEFT:
		//Check the position in the grid at row + 1, which is where the head would end up
		holdResult = GameGrid::CheckGridSpot(headToMove->GetHeadRow() + GridCheckDistance, headToMove->GetHeadCol());

		//if there is nothing occupying the space
		if (holdResult == GameGrid::CheckGridResult::OPEN || holdResult == GameGrid::CheckGridResult::SPOT_TAKEN)
		{
			//Move the centipede head down
			MoveDown(headToMove);

			//Set the current cardinal direction to point downwards, and to be switched to left after it's complete
			headToMove->SetMyMoveCardinal(CentipedeHead::MoveCardinal::DOWN);
		}
		//Bottom of the window
		else if (holdResult == GameGrid::CheckGridResult::WALL)
		{
			//Set the centipede to move up and finish by moving left in order to handle being at the bottom of the screen
			headToMove->SetMyMoveDir(CentipedeHead::UP_END_LEFT);

			//Set the move pattern to be the player zone now that the bottom of the screen has been reached
			headToMove->SetMyMovePattern(CentipedeHead::MovePattern::PLR_ZONE);

			//Recursively call HandleGridCheck to find correct movement pos
			HandleGridCheck(headToMove);
		}

		break;
	case CentipedeHead::DOWN_END_RIGHT:
		//Check the position in the grid at row + 1, which is where the head would end up
		holdResult = GameGrid::CheckGridSpot(headToMove->GetHeadRow() + GridCheckDistance, headToMove->GetHeadCol());

		//if there is nothing occupying the space
		if (holdResult == GameGrid::OPEN || holdResult == GameGrid::SPOT_TAKEN)
		{
			//Move the centipede head down
			MoveDown(headToMove);

			//Set the current cardinal direction to point downwards, and to be switched to left after it's complete
			headToMove->SetMyMoveCardinal(CentipedeHead::DOWN);
		}
		//Bottom of the window
		else if (holdResult == GameGrid::WALL)
		{
			//Set the centipede to move up and finish by moving right in order to handle being at the bottom of the screen
			headToMove->SetMyMoveDir(CentipedeHead::UP_END_RIGHT);

			//Set the move pattern to be the player zone now that the bottom of the screen has been reached
			headToMove->SetMyMovePattern(CentipedeHead::PLR_ZONE);

			//Recursively call HandleGridCheck to find correct movement pos
			HandleGridCheck(headToMove);
		}

		break;
	case CentipedeHead::UP_END_RIGHT:
		//Check if the head will be running into the plauer movement y-limit
		if (CheckForPlrArea(headToMove))
		{
			//Set the centipede head to be moving down and to the right given that it has reached the player movement y-limit
			headToMove->SetMyMoveDir(CentipedeHead::DOWN_END_RIGHT);

			//Set the movement pattern to be in MAIN_MOVE setting in which the head will be downward-bound
			headToMove->SetMyMovePattern(CentipedeHead::MAIN_MOVE);

			//Recursively call HandleGridCheck to perform the appropriate movement
			HandleGridCheck(headToMove);
		}
		else
		{
			//Move the centipede head up
			MoveUp(headToMove);

			//Set the cardinal movement direction to point up, and it will be switched to right after it has reached the next cell
			headToMove->SetMyMoveCardinal(CentipedeHead::UP);
		}

		break;
	case CentipedeHead::UP_END_LEFT:
		//Check if the head will be running into the plauer movement y-limit
		if (CheckForPlrArea(headToMove))
		{
			//Set the centipede head to be moving down and to the left given that it has reached the player movement y-limit
			headToMove->SetMyMoveDir(CentipedeHead::DOWN_END_LEFT);

			//Set the movement pattern to be in MAIN_MOVE setting in which the head will be downward-bound
			headToMove->SetMyMovePattern(CentipedeHead::MAIN_MOVE);

			//Recursively call HandleGridCheck to perform the appropriate movement
			HandleGridCheck(headToMove);
		}
		else
		{
			//Move the centipede head up
			MoveUp(headToMove);

			//Set the cardinal movement direction to point up, and it will be switched to left after it has reached the next cell
			headToMove->SetMyMoveCardinal(CentipedeHead::MoveCardinal::UP);
		}

		break;
	}

	

}

void CentipedeHeadMover::HandleMove_NoGridCheck(CentipedeHead* headToMove)
{
	switch (headToMove->GetMyMoveCardinal())
	{
	case CentipedeHead::LEFT:
		//Move the centipede head left
		MoveLeft(headToMove);

		break;

	case CentipedeHead::RIGHT:
		//Move the centipede head right
		MoveRight(headToMove);

		break;

	case CentipedeHead::UP:
		//Move the centipede head down
		MoveUp(headToMove);

		break;

	case CentipedeHead::DOWN:
		//Move the centipede head down
		MoveDown(headToMove);

		break;
	}
}

void CentipedeHeadMover::SetLeftDirection(CentipedeHead* headToMove)
{
	headToMove->SetMyMoveDir(CentipedeHead::LEFT_BOUND);
	headToMove->SetMyMoveCardinal(CentipedeHead::LEFT);
}

void CentipedeHeadMover::SetRightDirection(CentipedeHead* headToMove)
{
	headToMove->SetMyMoveDir(CentipedeHead::RIGHT_BOUND);
	headToMove->SetMyMoveCardinal(CentipedeHead::RIGHT);
}