#include "MoveLeftEndDownwards.h"
#include <iostream>
#include "MovementCollection.h"
#include <assert.h>
#include "CentipedeHead.h"
#include "CentipedeHeadMover.h"
#include "Grid.h"
#include "MoveFSM.h"
#include "GridManager.h"
#include "Player.h"
#include "PlayerManager.h"
#include "CentipedeHeadFactory.h"
#include "GameManager.h"

MoveLeftEndDownwards::MoveLeftEndDownwards()
{
	std::cout << "Initializing MoveLeftEndDownwards state\n";

	MyMoveOffsets = MovementCollection::OffsetsStraightLeft;
}
void MoveLeftEndDownwards::Show() const
{
	std::cout << "MoveLeftEndDownwards";
}

const MoveState* MoveLeftEndDownwards::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	int holdRow = chead->GetHeadRow();
	int holdCol = chead->GetHeadCol() - GridCheckDistance;

	//Check the position in the grid at col - 1, which is where the head would end up
	GameGrid::CheckGridResult holdResult = GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->CheckGridSpot(holdRow, holdCol);

	
	//if there is nothing occupying the space
	if (holdResult == GameGrid::OPEN)
	{
		pNextState = &MoveFSM::StateMoveLeftEndDownwards;
	}
	//Edge, shroom or letter?
	else if (holdResult == GameGrid::SPOT_TAKEN || holdResult == GameGrid::WALL || holdResult == GameGrid::BOTTOM_WINDOW)
	{
		//Bottom of the window
		if (CheckForBottomWindow(chead))
		{
			pNextState = (MoveState*)&MoveFSM::StateTurnUpSwitchToRight;

			CentipedeHeadFactory::SpawnPlayerAreaSoloHeads();
		}
		//Regular state processing 
		else
		{
			pNextState = (MoveState*)&MoveFSM::StateTurnDownSwitchToRight;
		}
	}
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

const MoveState* MoveLeftEndDownwards::GetNextState(int row, int col, sf::Vector2f pos) const
{
	const MoveState* pNextState;

	int holdCol = col - GridCheckDistance;

	//Check the position in the grid at col - 1, which is where the head would end up
	GameGrid::CheckGridResult holdResult = GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->CheckGridSpot(row, holdCol);


	//if there is nothing occupying the space
	if (holdResult == GameGrid::OPEN)
	{
		pNextState = &MoveFSM::StateMoveLeftEndDownwards;
	}
	//Edge, shroom or letter?
	else if (holdResult == GameGrid::SPOT_TAKEN || holdResult == GameGrid::WALL || holdResult == GameGrid::BOTTOM_WINDOW)
	{
		//Bottom of the window
		if (CheckForBottomWindow(row))
		{
			pNextState = (MoveState*)&MoveFSM::StateTurnUpSwitchToRight;

			CentipedeHeadFactory::SpawnPlayerAreaSoloHeads();
		}
		else
		{
			pNextState = (MoveState*)&MoveFSM::StateTurnDownSwitchToRight;
		}


	}
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

bool MoveLeftEndDownwards::CheckForBottomWindow(CentipedeHead* chead) const
{
	int holdRow = chead->GetHeadRow() + 1;
	if (holdRow > GameManager::GetGridMgr()->GetNumRows())
	{
		return true;
	}

	return false;

}

bool MoveLeftEndDownwards::CheckForBottomWindow(int row) const
{
	int holdRow = row + 1;
	if (holdRow > GameManager::GetGridMgr()->GetNumRows())
	{
		return true;
	}

	return false;

}

int MoveLeftEndDownwards::IncrementRow() const
{
	return RowIncrement;
}

int MoveLeftEndDownwards::IncrementCol() const
{
	return ColIncrement;
}

std::stack<int> MoveLeftEndDownwards::GetSpriteProperties(const int offsetArrIndex) const
{
	//Stack to store the sprite data in
	std::stack<int> holdSpriteData;

	//If the centipede has just entered this state, return true and update its sprite values
	if (offsetArrIndex == 0)
	{
		holdSpriteData.push(SpriteFirstFrame);
		holdSpriteData.push(SpriteLastFrame);
		holdSpriteData.push((int)SpriteScalar_X);
		holdSpriteData.push((int)SpriteScalar_Y);
	}
	//Else the stack will have no data and the centipede will check for this

	return holdSpriteData;
}
