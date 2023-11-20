#include "CentipedeHead.h"
#include "CentipedeBody.h"
#include "CentipedeHeadFactory.h"
#include "CentipedeBodyFactory.h"
#include <iostream>
#include "MovementCollection.h"
#include "MoveState.h"
#include "MoveFSM.h"
#include "Dart.h"
#include "MushroomFactory.h"
#include <stack>
#include "GridManager.h"
#include "DisplayOnDeathFactory.h"
#include "GameManager.h"

CentipedeHead::CentipedeHead()
{
	pCurrentState = (MoveState*) &MoveFSM::StateTurnDownSwitchToRight;

	CentiSprite = AnimatedSprite(ResourceManager::GetTexture("centipede_head"), SpriteFrameCountWidth, SpriteFrameCountHeight, SpriteFPS);

	CentiSprite.setOrigin(CentiSprite.getTextureRect().width / spriteOriginDiv, CentiSprite.getTextureRect().height / spriteOriginDiv);

	CentiSprite.scale(SpriteInitScale, SpriteInitScale);

	SetDrawOrder(CentipedeHeadFactory::GetCentipedeDrawOrder());

	incrementMoveArray = 0;

	UpdateSpriteValuesFromState();

	bitmap = ResourceManager::GetTextureBitmap("centipede_head");

	SetCollider(CentiSprite, bitmap, true);

	bodyFirstNode = nullptr;

	pHoldState = nullptr;

	holdSpeed = 0.0f;
	
}

void CentipedeHead::Initialize(sf::Vector2f p, int row, int col, const MoveState* setState, CentipedeBody* firstNode, int offsetIncr, float speed)
{
	pCurrentState = setState;

	incrementMoveArray = offsetIncr;

	UpdateSpriteValuesFromState();

	Pos = p;

	bodyFirstNode = firstNode;

	pHoldState = nullptr;

	CentiSprite.setPosition(Pos);

	//Initialize game variables of the CentipedeHead
	this->SetLifeState(GameObject::ALIVE);
	health = CentipedeSpawnHealth;

	//Store the initial row and column of the centipede 
	myRow = row;
	myCol = col;

	//Get the current speed of the centipede
	holdSpeed = speed;

	RegisterCollision<CentipedeHead>(*this);

	incrementMoveArrayAmount = GameManager::GetGridMgr()->GetPixelDistance() / (GameManager::GetGridMgr()->GetPixelDistance() / (int)speed);
	
}

void CentipedeHead::Destroy()
{
	ConsoleMsg::WriteLine("Destroyed centipede head!");
	DeregisterCollision<CentipedeHead>(*this);
}

void CentipedeHead::Update()
{
	float holdX = pCurrentState->GetMoveOffsets()[incrementMoveArray].GetColOffset() * holdSpeed;
	float holdY = pCurrentState->GetMoveOffsets()[incrementMoveArray].GetRowOffset() * holdSpeed;

	Pos.x += holdX;
	Pos.y += holdY;

	incrementMoveArray += incrementMoveArrayAmount;

	//If the movement index as exceeded the indices of the offset array
	if (incrementMoveArray >= MovementCollection::GetArrMax())
	{
		myCol += pCurrentState->IncrementCol();
		myRow += pCurrentState->IncrementRow();

		//if there is a body node to send to, but only if this is not a newly created centipede from a body which is the only case where pHoldState would not be nullptr
		if (bodyFirstNode != nullptr && pHoldState == nullptr)
		{
			//Tell the body parts to update their movement states by passing down the now old state
			bodyFirstNode->SetMoveState_FSM(pCurrentState);
		}

		if (pHoldState == nullptr)
		{
			pCurrentState = pCurrentState->GetNextState(this);
		}
		else
		{
			pCurrentState = pHoldState;
			pHoldState = nullptr;
		}

		incrementMoveArray = 0;
	}

	//Update the sprite from the current state's values
	UpdateSpriteValuesFromState();

	//Update the position of the sprite to match the object
	CentiSprite.setPosition(Pos);

	//Update the appearance of the sprite
	CentiSprite.Update();

}

void CentipedeHead::Draw()
{
	WindowManager::Window().draw(CentiSprite);
}

sf::Vector2f CentipedeHead::GetHeadPos()
{
	return Pos;
}

void CentipedeHead::SetHeadPos(sf::Vector2f newPos)
{
	Pos = newPos;
}

int CentipedeHead::GetHeadRow()
{
	return myRow;
}

int CentipedeHead::GetHeadCol()
{
	return myCol;
}

void CentipedeHead::SetHeadRow(int newRow)
{
	myRow = newRow;
}

void CentipedeHead::SetHeadCol(int newCol)
{
	myCol = newCol;
}

void CentipedeHead::SetBodyNodePtr(CentipedeBody* _firstBody)
{
	bodyFirstNode = _firstBody;
}

CentipedeBody* CentipedeHead::GetBodyNodePtr()
{
	return bodyFirstNode;
}

void CentipedeHead::SetMoveState_FSM(const MoveState* newState)
{
	pHoldState = newState;
}

void CentipedeHead::SetMoveIncrement(int newVal)
{
	//Add the old move increment val to account for any updates made in between the creation
	incrementMoveArray += newVal;
}

void CentipedeHead::privCreateMushroomFromBody()
{
	//Store the would-be position in the grid of the head
	int holdRow = myRow + pCurrentState->IncrementRow();
	int holdCol = myCol + pCurrentState->IncrementCol();

	//Create a mushroom in the would-be row and column of the centipede head
	MushroomFactory::CreateMushroom(holdRow, holdCol);
}

void CentipedeHead::privOnDeathCreateHead()
{
	if (bodyFirstNode != nullptr)
	{
		//Store the data of the next node in the list before creating the mushroom
		int holdRow = bodyFirstNode->GetBodyRow();
		int holdCol = bodyFirstNode->GetBodyCol();

		//Store the move state of the next node
		const MoveState* holdMoveState = bodyFirstNode->GetMyMoveState();

		//Store the position of the next node
		sf::Vector2f holdNextPos = bodyFirstNode->GetBodyPos();

		//Store the incrementor for the move array of the node
		int holdIncrementCount = bodyFirstNode->GetArrIncVal();

		//Get the node after the next node
		CentipedeBody* holdNext_NextBody = bodyFirstNode->GetNextPtr();

		CentipedeBodyFactory::DecrementBodyCount();

		//Mark the body part for destroy as the new head will take it's place
		bodyFirstNode->MarkForDestroy();

		CentipedeHead* holdHeadRef;

		//Change the properties of the first node of the new list to reflect the new head, if it exists
		if (holdNext_NextBody != nullptr)
		{
			//Create a new centipede head in the pos of the old node
			holdHeadRef = CentipedeHeadFactory::CreateCentipedeHead(holdNextPos, holdRow, holdCol, holdMoveState, holdSpeed, holdNext_NextBody, holdIncrementCount);

			//Increment the row and column to their would-be positions in order to check the next grid position
			int holdRowIncrement = holdMoveState->IncrementRow();
			int holdColInc = holdMoveState->IncrementCol();

			//Check the grid based on the would-be position of the head
			const MoveState* checkGrid = holdMoveState->GetNextState(holdRow + holdRowIncrement, holdCol + holdColInc, holdNextPos);

			//Queue the next movement for the new head so that it does not get out of grid position
			//Checks the grid space ahead of it's would-be position in the next cell
			holdHeadRef->SetMoveState_FSM(checkGrid);

			//Set the first node in the new list to have no previous ptr given that the head is behind it
			holdNext_NextBody->SetPrevPtr(nullptr);

			//tell the rest of the list to change their head ptrs
			holdNext_NextBody->UpdateBodyData(holdHeadRef, holdMoveState);
		}
		else
		{
			//Create a new centipede head in the pos of the old node
			holdHeadRef = CentipedeHeadFactory::CreateCentipedeHead(holdNextPos, holdRow, holdCol, holdMoveState, holdSpeed, nullptr, holdIncrementCount);

			
		}
	}
}


void CentipedeHead::Collision(Dart* other)
{
	//Reduce the health of the Scorpion
	health -= GetDmgAmount();

	//Destroy the dart so that when the mushroom is spawned, it doesnt damage it
	other->GameObject::MarkForDestroy();

	ConsoleMsg::WriteLine("Centipede head took damage!");

	//Centipede dies at health <= 0
	if (health <= GetDeathHP())
	{
		//Create an explosion at the centi head pos
		DisplayOnDeathFactory::CreateExplosion1By1(Pos);

		//Tell the head factory to send the death score command to the score manager
		CentipedeHeadFactory::SendDeathCommandForScore();

		CentipedeHeadFactory::DecrementHeadCount();

		//Mark the centipede head for deletion by the engine
		GameObject::MarkForDestroy();

		DisplayOnDeathFactory::SendSoundCommand();

		privCreateMushroomFromBody();

		privOnDeathCreateHead();

		//Mark the Scorpion as dead
		this->SetLifeState(GameObject::DEAD);

		
	}
}

void CentipedeHead::UpdateSpriteValuesFromState()
{
	std::stack<int> holdSpriteData = pCurrentState->GetSpriteProperties(incrementMoveArray);

	//if the stack is not empty, update the sprite with the values from the current state
	if (!holdSpriteData.empty())
	{
		SpriteFlip_Y = (float)holdSpriteData.top();
		holdSpriteData.pop();

		SpriteFlip_X = (float)holdSpriteData.top();
		holdSpriteData.pop();

		SpriteLastFrame = holdSpriteData.top();
		holdSpriteData.pop();

		SpriteFirstFrame = holdSpriteData.top();
		holdSpriteData.pop();

		CentiSprite.setScale(SpriteFlip_X, SpriteFlip_Y);

		//Sets the first and the last frame of the section of the sprite sheet
		CentiSprite.SetAnimation(SpriteFirstFrame, SpriteLastFrame);
	}
}

