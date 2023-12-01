#include "CentipedeBody.h"
#include "CentipedeHead.h"
#include "CentipedeBodyFactory.h"
#include "CentipedeHeadFactory.h"
#include "MushroomFactory.h"
#include <iostream>
#include "MovementCollection.h"
#include "MoveState.h"
#include "MoveFSM.h"
#include "Dart.h"
#include "GridManager.h"
#include "DisplayOnDeathFactory.h"
#include "GameManager.h"

CentipedeBody::CentipedeBody()
{
	pCurrentState = (MoveState*)&MoveFSM::StateTurnDownSwitchToRight;

	//Initialize the sprite and attach it to the Body
	CentiSprite = AnimatedSprite(ResourceManager::GetTexture("centipede_segment"), SpriteFrameCountWidth, SpriteFrameCountHeight, SpriteFPS);

	CentiSprite.setOrigin(CentiSprite.getTextureRect().width / spriteOriginDiv, CentiSprite.getTextureRect().height / spriteOriginDiv);

	CentiSprite.scale(SpriteInitScale, SpriteInitScale);

	bitmap = ResourceManager::GetTextureBitmap("centipede_segment");

	SetCollider(CentiSprite, bitmap, true);

	SetDrawOrder(CentipedeHeadFactory::GetCentipedeDrawOrder());

	incrementMoveArray = 0;

	bodyNextNode = nullptr;

	bodyPrevNode = nullptr;

	headNode = nullptr;

	pHoldState = nullptr;

	holdSpeed = 0.0f;
}

void CentipedeBody::Initialize(sf::Vector2f p, int row, int col, CentipedeBody* _nextBody, CentipedeBody* _prevBody, CentipedeHead* _head, float speed)
{
	//Set the initial movement state of the centipede body
	pCurrentState = (MoveState*)&MoveFSM::StateTurnDownSwitchToRight;

	//Initialize the pointer refs to the linked list items
	bodyNextNode = _nextBody;
	bodyPrevNode = _prevBody;
	headNode = _head;
	pHoldState = nullptr;

	Pos = p;

	incrementMoveArray = 0;

	UpdateSpriteValuesFromState();

	CentiSprite.setPosition(Pos);

	//Initialize game variables of the CentipedeBody
	this->SetLifeState(GameObject::ALIVE);
	health = CentipedeSpawnHealth;

	//Store the initial row and column of the centipede 
	myRow = row;
	myCol = col;

	//Get the current speed of the centipede
	holdSpeed = speed;

	RegisterCollision<CentipedeBody>(*this);

	incrementMoveArrayAmount = GameManager::GetGridMgr()->GetPixelDistance() / (GameManager::GetGridMgr()->GetPixelDistance() / (int)speed);
	
}

void CentipedeBody::Destroy()
{

	ConsoleMsg::WriteLine("Destroyed centipede Body!");
	DeregisterCollision<CentipedeBody>(*this);
}

void CentipedeBody::Update()
{
	//Get the position offset for the current state
	float holdX = pCurrentState->GetMoveOffsets()[incrementMoveArray].GetColOffset() * holdSpeed;
	float holdY = pCurrentState->GetMoveOffsets()[incrementMoveArray].GetRowOffset() * holdSpeed;
	Pos.x += holdX;
	Pos.y += holdY;

	//Count the number of frames in which the body has moved so that it can retain it's grid position
	incrementMoveArray += incrementMoveArrayAmount;
	
	if (incrementMoveArray >= MovementCollection::GetArrMax())
	{
		//Update grid position upon exiting the previous cell
		if (pHoldState != nullptr)
		{
			//Update the row and column of the body, and reset it's counter
			privUpdateMyRowCol();
			incrementMoveArray = 0;

			pCurrentState = pHoldState;

			pHoldState = nullptr;
		}
	}

	//Update the sprite from the current state's values
	UpdateSpriteValuesFromState();

	//Update the position of the sprite to match the object
	CentiSprite.setPosition(Pos);

	//Update the appearance of the sprite
	CentiSprite.Update();

}

void CentipedeBody::Draw()
{
	WindowManager::Window().draw(CentiSprite);
}

sf::Vector2f CentipedeBody::GetBodyPos()
{
	return Pos;
}

void CentipedeBody::SetBodyPos(sf::Vector2f newPos)
{
	Pos = newPos;
}

int CentipedeBody::GetBodyRow()
{
	return myRow;
}

int CentipedeBody::GetBodyCol()
{
	return myCol;
}

void CentipedeBody::SetBodyRow(int newRow)
{
	myRow = newRow;
}

void CentipedeBody::SetBodyCol(int newCol)
{
	myCol = newCol;
}

void CentipedeBody::SetNextPtr(CentipedeBody* _nextPtr)
{
	bodyNextNode = _nextPtr;
}
void CentipedeBody::SetPrevPtr(CentipedeBody* _prevPtr)
{
	bodyPrevNode = _prevPtr;
}
CentipedeBody* CentipedeBody::GetNextPtr()
{
	return bodyNextNode;
}
CentipedeBody* CentipedeBody::GetPrevPtr()
{
	return bodyPrevNode;
}

void CentipedeBody::SetMoveState_FSM(const MoveState* newState)
{
	//Give the next body part this nodes state and tell the rest of the body parts to pass down their states
	if (bodyNextNode != nullptr)
	{
		bodyNextNode->SetMoveState_FSM(pCurrentState);
	}

	pHoldState = newState;

	
}

const MoveState* CentipedeBody::GetMyMoveState()
{
	return pCurrentState;
}

int CentipedeBody::GetArrIncVal()
{
	return incrementMoveArray;
}

void CentipedeBody::privUpdateMyRowCol()
{
	myCol += pCurrentState->IncrementCol();
	myRow += pCurrentState->IncrementRow();

	incrementMoveArray = 0;
}

void CentipedeBody::Collision(Dart* other)
{
	//Destroy the dart so that when the mushroom is spawned, it doesnt damage it
	other->GameObject::MarkForDestroy();

	//Reduce the health of the Scorpion
	health -= GetDmgAmount();

	ConsoleMsg::WriteLine("Centipede Body took damage!");

	//Scorpion dies at health <= 0
	if (health <= GetDeathHP())
	{
		//Create an explosion at the centi body pos
		DisplayOnDeathFactory::CreateExplosion1By1(Pos);

		//Tell the body factory to send the death score command to the score manager
		CentipedeBodyFactory::SendDeathCommandForScore();

		CentipedeBodyFactory::DecrementBodyCount();

		//Mark the CentipedeBody for deletion by the engine
		GameObject::MarkForDestroy();

		DisplayOnDeathFactory::SendSoundCommand();

		//Create a mushroom from the body in the would-be row and col pos
		privCreateMushroomFromBody();

		//Split the centipede into two halves with respective heads from the point at which this node was shot
		privOnDeathCreateHead();

		//Mark the Scorpion as dead
		this->SetLifeState(GameObject::DEAD);

		
	}
}

void CentipedeBody::privCreateMushroomFromBody()
{
	//Store the would-be position in the grid of the body part
	int holdRow = myRow + pCurrentState->IncrementRow();
	int holdCol = myCol + pCurrentState->IncrementCol();

	//Create a mushroom in the would-be row and column of the centipede body
	MushroomFactory::CreateMushroom(holdRow, holdCol);
}

void CentipedeBody::privOnDeathCreateHead()
{
	//If there is a body node in front of this one, set it's next ptr to be nullptr now that this is destroyed
	if (bodyPrevNode != nullptr)
	{
		bodyPrevNode->SetNextPtr(nullptr);
	}

	if (headNode != nullptr)
	{
		//If the head is pointing to this node, set that pointer to nullptr now that this is destroyed
		if (headNode->GetBodyNodePtr() == this)
		{
			headNode->SetBodyNodePtr(nullptr);
		}
	}


	//If there is a body node following this one, replace it with a mushroom
	if (bodyNextNode != nullptr)
	{
		//Store the data of the next node in the list before creating the mushroom
		int holdRow = bodyNextNode->GetBodyRow();
		int holdCol = bodyNextNode->GetBodyCol();

		//Store the move state of the next node
		const MoveState* holdMoveState = bodyNextNode->pCurrentState;

		//Store the position of the next node
		sf::Vector2f holdNextPos = bodyNextNode->Pos;

		//Store the incrementor for the move array of the node
		int holdIncrementCount = bodyNextNode->incrementMoveArray;

		CentipedeBodyFactory::DecrementBodyCount();

		//Mark the body part for destroy as the new head will take it's place
		bodyNextNode->MarkForDestroy();

		CentipedeHead* holdHeadRef = nullptr;


		if (bodyNextNode->bodyNextNode != nullptr)
		{
			//Get the node after the next node
			CentipedeBody* holdNext_NextBody = bodyNextNode->bodyNextNode;

			//Create a new centipede head in the pos of the old node
			//Sets the next node after the new head, if it exists, as the first node in the list for this head
			//Sets the offset incrementor that the node previously had
			holdHeadRef = CentipedeHeadFactory::CreateCentipedeHead(holdNextPos, holdRow, holdCol, holdMoveState, CentipedeHeadFactory::GetHeadSpeed(), holdNext_NextBody, holdIncrementCount);

			//Increment the row and column to their would-be positions in order to check the next grid position
			int holdRowIncrement = holdMoveState->IncrementRow();
			int holdColInc = holdMoveState->IncrementCol();

			//Check the grid based on the would-be position of the head
			const MoveState* checkGrid = holdMoveState->GetNextState(holdRow + holdRowIncrement, holdCol + holdColInc, holdNextPos);

			//Queue the next movement for the new head so that it does not get out of grid position
			//Checks the grid space ahead of it's would-be position in the next cell
			holdHeadRef->SetMoveState_FSM(checkGrid);

			//Set the first node in the new list to have no previous ptr given that the head is behind it
			holdNext_NextBody->bodyPrevNode = nullptr;

			//tell the rest of the list to change their head ptrs and set their next movement states
			holdNext_NextBody->privUpdateBodyData(holdHeadRef, holdMoveState);
		}
		else
		{
			//Create a new centipede head in the pos of the old node
			//Sets the next node after the new head, if it exists, as the first node in the list for this head
			//Sets the offset incrementor that the node previously had
			holdHeadRef = CentipedeHeadFactory::CreateCentipedeHead(holdNextPos, holdRow, holdCol, holdMoveState, CentipedeHeadFactory::GetHeadSpeed(), nullptr, holdIncrementCount);

		}
	}
}

void CentipedeBody::privUpdateBodyData(CentipedeHead* _newHead, const MoveState* newState)
{
	//Update the head ptr to the new head ptr
	headNode = _newHead;

	//Update the next state for each of the body parts
	pHoldState = newState;

	//Tell the rest of the list, if present, to update theirs too
	if (bodyNextNode != nullptr)
	{
		//Send the body's current state to the next one in the list
		bodyNextNode->privUpdateBodyData(_newHead, pCurrentState);
	}
	
}

void CentipedeBody::UpdateBodyData(CentipedeHead* headRef, const MoveState* newState)
{
	privUpdateBodyData(headRef, newState);
}

void CentipedeBody::UpdateSpriteValuesFromState()
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