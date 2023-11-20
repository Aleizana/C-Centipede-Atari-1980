#include "TurnUpSwitchToLeft.h"
#include <iostream>
#include "MovementCollection.h"
#include <assert.h>
#include "CentipedeHead.h"
#include "CentipedeHeadMover.h"
#include "Grid.h"
#include "MoveFSM.h"
#include "GridManager.h"
#include "PlayerManager.h"
#include "Player.h"
#include "GameManager.h"

TurnUpSwitchToLeft::TurnUpSwitchToLeft()
{
	std::cout << "Initializing TurnUpSwitchToLeft state\n";

	MyMoveOffsets = MovementCollection::OffsetsTurnUpEndLeft;
}
void TurnUpSwitchToLeft::Show() const
{
	std::cout << "TurnUpSwitchToLeft";
}
const MoveState* TurnUpSwitchToLeft::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	int holdRow = chead->GetHeadRow();
	int holdCol = chead->GetHeadCol() - GridCheckDistance;

	//Check the position in the grid at row - 1, which is where the head would end up
	GameGrid::CheckGridResult holdResult = GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->CheckGridSpot(holdRow, holdCol);

	
	//if there is nothing occupying the space
	if (holdResult == GameGrid::OPEN)
	{
		pNextState = (MoveState*)&MoveFSM::StateMoveLeftEndUpwards;
	}
	//Edge, shroom or letter?
	else if (holdResult == GameGrid::SPOT_TAKEN || holdResult == GameGrid::WALL)
	{
		//Player area limit check
		if (CheckForPlrArea(chead))
		{
			pNextState = (MoveState*)&MoveFSM::StateTurnDownSwitchToRight;
		}
		else
		{
			pNextState = (MoveState*)&MoveFSM::StateTurnUpSwitchToRight;
		}
		
	}
	//Centipede touched poison mushroom
	else if (holdResult == GameGrid::POISONED)
	{
		ConsoleMsg::WriteLine("Centipede touched POISON!");

		pNextState = (MoveState*)&MoveFSM::StatePoisonedTurnDownEndRight;
	}
	else // invalid guard
	{
		assert(false && "Invalid Grid Result!");
		pNextState = nullptr;
	}


	return pNextState;
}

const MoveState* TurnUpSwitchToLeft::GetNextState(int row, int col, sf::Vector2f pos) const
{
	const MoveState* pNextState;

	int holdCol = col - GridCheckDistance;

	//Check the position in the grid at row - 1, which is where the head would end up
	GameGrid::CheckGridResult holdResult = GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->CheckGridSpot(row, holdCol);


	//if there is nothing occupying the space
	if (holdResult == GameGrid::OPEN)
	{
		pNextState = (MoveState*)&MoveFSM::StateMoveLeftEndUpwards;
	}
	//Edge, shroom or letter?
	else if (holdResult == GameGrid::SPOT_TAKEN || holdResult == GameGrid::WALL)
	{
		//Player area limit check
		if (CheckForPlrArea(pos))
		{
			pNextState = (MoveState*)&MoveFSM::StateTurnDownSwitchToRight;
		}
		else
		{
			pNextState = (MoveState*)&MoveFSM::StateTurnUpSwitchToRight;
		}

	}
	//Centipede touched poison mushroom
	else if (holdResult == GameGrid::POISONED)
	{
		ConsoleMsg::WriteLine("Centipede touched POISON!");

		pNextState = (MoveState*)&MoveFSM::StatePoisonedTurnDownEndRight;
	}
	else // invalid guard
	{
		assert(false && "Invalid Grid Result!");
		pNextState = nullptr;
	}


	return pNextState;
}

const bool TurnUpSwitchToLeft::CheckForPlrArea(CentipedeHead* headToMove) const
{
	//Check if centipede head will be moving into the player area limit and return true if so
	//The player area limit is offset by the same value that the centipede head pos is offset at spawn
	if (headToMove->GetHeadPos().y < GameManager::GetPlayerMgr()->GetPlayerAreaLimit())
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool TurnUpSwitchToLeft::CheckForPlrArea(sf::Vector2f pos) const
{
	//Check if centipede head will be moving into the player area limit and return true if so
	//The player area limit is offset by the same value that the centipede head pos is offset at spawn
	if (pos.y < GameManager::GetPlayerMgr()->GetPlayerAreaLimit())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int TurnUpSwitchToLeft::IncrementRow() const
{
	return RowIncrement;
}

int TurnUpSwitchToLeft::IncrementCol() const
{
	return ColIncrement;
}

std::stack<int> TurnUpSwitchToLeft::GetSpriteProperties(const int offsetArrIndex) const
{
	//Stack to store the sprite data in
	std::stack<int> holdSpriteData;

	//If the centipede has just entered this state, return true and update its sprite values
	if (offsetArrIndex == 0)
	{
		holdSpriteData.push(SpriteFirstFrame_FirstState);
		holdSpriteData.push(SpriteLastFrame_FirstState);
		holdSpriteData.push((int)SpriteScalar_X_FirstState);
		holdSpriteData.push((int)SpriteScalar_Y_FirstState);
	}
	//Second sprite state once the sprite has gone halfway through the offset array
	else if (offsetArrIndex >= MovementCollection::GetArrMax() / ArrMaxHalf)
	{
		holdSpriteData.push(SpriteFirstFrame_SecState);
		holdSpriteData.push(SpriteLastFrame_SecState);
		holdSpriteData.push((int)SpriteScalar_X_SecState);
		holdSpriteData.push((int)SpriteScalar_Y_SecState);
	}
	//Else the stack will have no data and the centipede will check for this

	return holdSpriteData;
}