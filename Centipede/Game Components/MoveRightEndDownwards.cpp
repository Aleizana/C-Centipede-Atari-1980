#include "MoveRightEndDownwards.h"
#include <iostream>
#include "MovementCollection.h"
#include <assert.h>
#include "CentipedeHead.h"
#include "CentipedeHeadMover.h"
#include "Grid.h"
#include "MoveFSM.h"
#include "GridManager.h"
#include "Player.h"
#include "CentipedeHeadFactory.h"
#include "PlayerManager.h"
#include "GameManager.h"

MoveRightEndDownwards::MoveRightEndDownwards()
{
	std::cout << "Initializing MoveRightEndDownwards state\n";

	MyMoveOffsets = MovementCollection::OffsetsStraightRight;
}
void MoveRightEndDownwards::Show() const
{
	std::cout << "MoveRightEndDownwards";
}

const MoveState* MoveRightEndDownwards::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	int holdRow = chead->GetHeadRow();
	int holdCol = chead->GetHeadCol() + GridCheckDistance;

	//Check the position in the grid at col + 1, which is where the head would end up
	GameGrid::CheckGridResult holdResult = GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->CheckGridSpot(holdRow, holdCol);

	//if there is nothing occupying the space
	if (holdResult == GameGrid::OPEN)
	{
		pNextState = &MoveFSM::StateMoveRightEndDownwards;
	}
	//Edge, shroom or letter?
	else if (holdResult == GameGrid::SPOT_TAKEN || holdResult == GameGrid::WALL || holdResult == GameGrid::BOTTOM_WINDOW)
	{
		//Bottom of the window
		if (CheckForBottomWindow(chead))
		{
			pNextState = (MoveState*)&MoveFSM::StateTurnUpSwitchToLeft;

			CentipedeHeadFactory::SpawnPlayerAreaSoloHeads();
		}
		else
		{
			pNextState = (MoveState*)&MoveFSM::StateTurnDownSwitchToLeft;

			
		}
		
	}
	//Centipede touched poison mushroom
	else if (holdResult == GameGrid::POISONED)
	{
		ConsoleMsg::WriteLine("Centipede touched POISON!");

		pNextState = (MoveState*)&MoveFSM::StatePoisonedTurnDownEndLeft;
	}
	else // invalid guard
	{
		assert(false && "Invalid Grid Result!");
		pNextState = nullptr;
	}


	return pNextState;
}

const MoveState* MoveRightEndDownwards::GetNextState(int row, int col, sf::Vector2f pos) const
{
	const MoveState* pNextState;

	int holdCol = col + GridCheckDistance;

	//Check the position in the grid at col + 1, which is where the head would end up
	GameGrid::CheckGridResult holdResult = GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->CheckGridSpot(row, holdCol);

	//if there is nothing occupying the space
	if (holdResult == GameGrid::OPEN)
	{
		pNextState = &MoveFSM::StateMoveRightEndDownwards;
	}
	//Edge, shroom or letter?
	else if (holdResult == GameGrid::SPOT_TAKEN || holdResult == GameGrid::WALL || holdResult == GameGrid::BOTTOM_WINDOW)
	{
		//Bottom of the window
		if (CheckForBottomWindow(row))
		{
			pNextState = (MoveState*)&MoveFSM::StateTurnUpSwitchToLeft;

			CentipedeHeadFactory::SpawnPlayerAreaSoloHeads();
		}
		else
		{
			pNextState = (MoveState*)&MoveFSM::StateTurnDownSwitchToLeft;
		}

	}
	//Centipede touched poison mushroom
	else if (holdResult == GameGrid::POISONED)
	{
		ConsoleMsg::WriteLine("Centipede touched POISON!");

		pNextState = (MoveState*)&MoveFSM::StatePoisonedTurnDownEndLeft;
	}
	else // invalid guard
	{
		assert(false && "Invalid Grid Result!");
		pNextState = nullptr;
	}


	return pNextState;
}

bool MoveRightEndDownwards::CheckForBottomWindow(CentipedeHead* chead) const
{
	int holdRow = chead->GetHeadRow() + 1;
	if (holdRow <= GameManager::GetGridMgr()->GetNumRows())
	{
		return false;
	}

	return true;

}

bool MoveRightEndDownwards::CheckForBottomWindow(int row) const
{
	int holdRow = row + 1;
	if (holdRow <= GameManager::GetGridMgr()->GetNumRows())
	{
		return false;
	}

	return true;

}

int MoveRightEndDownwards::IncrementRow() const
{
	return RowIncrement;
}

int MoveRightEndDownwards::IncrementCol() const
{
	return ColIncrement;
}

std::stack<int> MoveRightEndDownwards::GetSpriteProperties(const int offsetArrIndex) const
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