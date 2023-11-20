// Spider
// // Andre Berthiaume, March 2013

#include "Spider.h"
#include <math.h>
#include "Grid.h"
#include "SpiderMover.h"
#include "SpiderFactory.h"
#include "Dart.h"
#include "DisplayOnDeathFactory.h"
#include "SpiderMoveState.h"

Spider::Spider()
{
	bitmap = &ResourceManager::GetTextureBitmap("spider");

	//Frame count width is the width of the sprite sheet divided by the number of diff sprites you have in the row
	//Frame count height is the height of the sprite sheet divided by the number of diff sprites you have in the column
	//Frames per second is the speed at which you will cycle through the sprites
	SpiderSprite = AnimatedSprite(ResourceManager::GetTexture("spider"), SpiderFrameCountWidth, SpiderFrameCountHeight, SpiderSpriteFPS);

	//Sets the first and the last frame of the sprite sheet
	SpiderSprite.SetAnimation(SpiderSpriteFirstFrame, SpiderSpriteLastFrame);

	SpiderSprite.scale(SpiderScalar, SpiderScalar);

	//Set the origin (0,0) of the sprite
	SpiderSprite.setOrigin(SpiderSprite.getTextureRect().width / spriteOriginSizeDivisor, SpiderSprite.getTextureRect().height / spriteOriginSizeDivisor);

	//Set and register Spider collision
	SetCollider(SpiderSprite, *bitmap);

	moveArrIncrementor = 0;
}

void Spider::Initialize(sf::Vector2f p, SpiderMover* _moverRef, SpiderFactory::SpiderMainDirection newDir)
{
	Pos = p;

	RegisterCollision<Spider>(*this);

	myMoverRef = _moverRef;

	//Initialize game variables of the Spider
	this->SetLifeState(GameObject::ALIVE);
	health = SpiderSpawnHealth;
	SpiderRow = 0;
	SpiderCol = 0;

	moveArrIncrementor = 0;

	currSpiderDir = newDir;

	//Set the movestate to be nullptr initially
	pCurrMoveState = nullptr;

	//Up and down will not be tested for initially, so that the spider can walk onto the screen
	//Test for the left move state values specifically
	if (currSpiderDir == SpiderFactory::SpiderMainDirection::LEFT)
	{
		pCurrMoveState = SpiderFactory::GetLeftDirState();
	}
	//Test for the right move state values specifically
	else if (currSpiderDir == SpiderFactory::SpiderMainDirection::RIGHT)
	{
		pCurrMoveState = SpiderFactory::GetRightDirState();
	}
	else
	{
		assert(false && "Invalid direction");
	}
}

void Spider::SetRowCol(int row, int col)
{
	SpiderRow = row;
	SpiderCol = col;
}

void Spider::Update()
{
	//Handle updating the position of the Spider
	myMoverRef->HandleSpiderMove(this, moveArrIncrementor);

	//You HAVE to do this every update or else the position will go to (0,0)
	SpiderSprite.setPosition(Pos);

	//Update the appearance of the sprite
	SpiderSprite.Update();
}

void Spider::Draw()
{
	WindowManager::Window().draw(SpiderSprite);
}

void Spider::Collision(Dart* other)
{
	//Mark the dart for destroy so it can't kill anything else
	other->GameObject::MarkForDestroy();

	//Reduce the health of the Spider
	health -= GetDmgAmount();

	//Spider dies at health <= 0
	if (health <= GetDeathHP())
	{
		DisplayOnDeathFactory::SendSoundCommand();

		//Create an explosion at the spider's pos
		//DisplayOnDeathFactory::CreateExplosion1By1(Pos);

		//Tell the spider factory to send a scoring command and pass it the spider's position
		SpiderFactory::SendDeathCommandForScore(Pos);

		//Mark the Spider for deletion by the engine
		GameObject::MarkForDestroy();

		//Mark the Spider as dead
		this->SetLifeState(GameObject::DEAD);
	}
}

void Spider::Destroy()
{

	ConsoleMsg::WriteLine("Deleted Spider!");
	DeregisterCollision<Spider>(*this);
}

void Spider::SetMyPos(sf::Vector2f _newPos)
{
	Pos = _newPos;
}

sf::Vector2f Spider::GetMyPos()
{
	return Pos;
}

SpiderFactory::SpiderMainDirection Spider::GetSpiderDir()
{
	return currSpiderDir;
}

const SpiderMoveState* Spider::GetMyState()
{
	return pCurrMoveState;
}

void Spider::GetNextState()
{
	pCurrMoveState = pCurrMoveState->GetNextState(this);
}

int Spider::GetMyRow()
{
	return SpiderRow;
}

void Spider::SetMyRow(int newRow)
{
	SpiderRow = newRow;
}

int Spider::GetMyCol()
{
	return SpiderCol;
}