#include "TurnDownSwitchToRight.h"
#include <iostream>
#include "MovementCollection.h"
#include <assert.h>
#include "CentipedeHead.h"
#include "CentipedeHeadMover.h"
#include "Grid.h"
#include "MoveFSM.h"
#include "PlayerManager.h"
#include "Player.h"
#include "GridManager.h"
#include "CentipedeHeadFactory.h"
#include "GameManager.h"

TurnDownSwitchToRight::TurnDownSwitchToRight()
{
	std::cout << "Initializing TurnDownSwitchToRight state\n";

	MyMoveOffsets = MovementCollection::OffsetsTurnDownEndRight;
}
void TurnDownSwitchToRight::Show() const
{
	std::cout << "TurnDownSwitchToRight";
}
const MoveState* TurnDownSwitchToRight::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	int holdRow = chead->GetHeadRow();
	int holdCol = chead->GetHeadCol() + GridCheckDistance;

	//Check the position in the grid at row + 1, which is where the head would end up
	GameGrid::CheckGridResult holdResult = GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->CheckGridSpot(holdRow, holdCol);

	//if there is nothing occupying the space or if there is a mushroom, but the centipede will move through the mushroom
	if (holdResult == GameGrid::OPEN)
	{
		pNextState = (MoveState*)&MoveFSM::StateMoveRightEndDownwards;
	}
	//Bottom of the window
	else if (holdResult == GameGrid::BOTTOM_WINDOW)
	{
		pNextState = (MoveState*)&MoveFSM::StateTurnUpSwitchToLeft;

		CentipedeHeadFactory::SpawnPlayerAreaSoloHeads();
	}
	//Edge, unreachable in this state
	else if (holdResult == GameGrid::WALL || holdResult == GameGrid::SPOT_TAKEN)
	{
		pNextState = (MoveState*)&MoveFSM::StateTurnDownSwitchToLeft;
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

const MoveState* TurnDownSwitchToRight::GetNextState(int row, int col, sf::Vector2f pos) const
{
	const MoveState* pNextState;

	int holdCol = col + GridCheckDistance;

	//Check the position in the grid at row + 1, which is where the head would end up
	GameGrid::CheckGridResult holdResult = GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->CheckGridSpot(row, holdCol);

	//if there is nothing occupying the space or if there is a mushroom, but the centipede will move through the mushroom
	if (holdResult == GameGrid::OPEN)
	{
		pNextState = (MoveState*)&MoveFSM::StateMoveRightEndDownwards;
	}
	//Bottom of the window
	else if (holdResult == GameGrid::BOTTOM_WINDOW)
	{
		pNextState = (MoveState*)&MoveFSM::StateTurnUpSwitchToLeft;

		CentipedeHeadFactory::SpawnPlayerAreaSoloHeads();
	}
	//Edge, unreachable in this state
	else if (holdResult == GameGrid::WALL || holdResult == GameGrid::SPOT_TAKEN)
	{
		pNextState = (MoveState*)&MoveFSM::StateTurnDownSwitchToLeft;
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

std::stack<int> TurnDownSwitchToRight::GetSpriteProperties(const int offsetArrIndex) const
{
	//Stack to store the sprite data in
	std::stack<int> holdSpriteData;

	//If the centipede has just entered this state, return true and update its sprite values
	if (offsetArrIndex == 0)
	{
		holdSpriteData.push(SpriteFirstFrame_FirstState);
		holdSpriteData.push(SpriteLastFrame_FirstState);
		holdSpriteData.push((int)SpriteScalar_X);
		holdSpriteData.push((int)SpriteScalar_Y);
	}
	//Second sprite state once the sprite has gone halfway through the offset array
	else if (offsetArrIndex == MovementCollection::GetArrMax() / ArrMaxHalf)
	{
		holdSpriteData.push(SpriteFirstFrame_SecState);
		holdSpriteData.push(SpriteLastFrame_SecState);
		holdSpriteData.push((int)SpriteScalar_X);
		holdSpriteData.push((int)SpriteScalar_Y);
	}
	//Else the stack will have no data and the centipede will check for this

	return holdSpriteData;
}

int TurnDownSwitchToRight::IncrementRow() const
{
	return RowIncrement;
}

int TurnDownSwitchToRight::IncrementCol() const
{
	return ColIncrement;
}