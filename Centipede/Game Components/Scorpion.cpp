/// Scorpion
// // Andre Berthiaume, March 2013

#include "Scorpion.h"
#include <math.h>
#include "Grid.h"
#include "ScorpionMover.h"
#include "ScorpionFactory.h"
#include "Dart.h"
#include "DisplayOnDeathFactory.h"
#include "ScorpionMoveBaseState.h"
#include "GameManager.h"
#include "GridManager.h"

Scorpion::Scorpion()
{
	bitmap = &ResourceManager::GetTextureBitmap("scorpion");

	//Frame count width is the width of the sprite sheet divided by the number of diff sprites you have in the row
	//Frame count height is the height of the sprite sheet divided by the number of diff sprites you have in the column
	//Frames per second is the speed at which you will cycle through the sprites
	ScorpionSprite = AnimatedSprite(ResourceManager::GetTexture("scorpion"), ScorpionFrameCountWidth, ScorpionFrameCountHeight, ScorpionSpriteFPS);

	//Sets the first and the last frame of the sprite sheet
	ScorpionSprite.SetAnimation(ScorpionSpriteFirstFrame, ScorpionSpriteLastFrame);

	//Set the origin (0,0) of the sprite
	ScorpionSprite.setOrigin(ScorpionSprite.getTextureRect().width / spriteOriginSizeDivisor, ScorpionSprite.getTextureRect().height / spriteOriginSizeDivisor);

	//Set and register Scorpion collision
	SetCollider(ScorpionSprite, *bitmap);

	health = 0;

	flippedSprite = false;

	pCurrState = nullptr;

	countMovement = 0;
}

void Scorpion::Initialize(sf::Vector2f p, ScorpionMover* _moverRef, ScorpionMoveBaseState* setDir)
{
	Pos = p;

	RegisterCollision<Scorpion>(*this);

	//Store a reference to the Scorpion mover
	myMoverRef = _moverRef;

	pCurrState = setDir;

	float holdSpriteScalar = pCurrState->GetSpriteDirFromState();

	ScorpionSprite.setScale(holdSpriteScalar, spriteFlipByScale);


	//Initialize game variables of the Scorpion
	this->SetLifeState(GameObject::ALIVE);
	health = ScorpionSpawnHealth;
	ScorpionRow = 0;
	ScorpionCol = 0;

	countMovement = 0;
}

void Scorpion::SetRowCol(int row, int col)
{
	ScorpionRow = row;
	ScorpionCol = col;
}

void Scorpion::Update()
{
	pCurrState->HandleScorpionMove(this, countMovement, GameManager::GetGridMgr()->GetPixelDistance());

	//You HAVE to do this every update or else the position will go to (0,0)
	ScorpionSprite.setPosition(Pos);

	//Update the appearance of the sprite
	ScorpionSprite.Update();
}

void Scorpion::Draw()
{
	WindowManager::Window().draw(ScorpionSprite);
}

void Scorpion::Collision(Dart* other)
{
	//Mark the dart for destroy so it can't kill anything else
	other->GameObject::MarkForDestroy();

	//Reduce the health of the Scorpion
	health -= GetDmgAmount();

	ConsoleMsg::WriteLine("Scorpion took damage!");

	//Scorpion dies at health <= 0
	if (health <= GetDeathHP())
	{
		DisplayOnDeathFactory::SendSoundCommand();

		ScorpionFactory::DecrementScorpionCount();

		ScorpionFactory::StopScorpionLoop();
		
		//Create an explosion at the scorpions pos
		DisplayOnDeathFactory::CreateExplosion1By1(Pos);

		//Initiate the scoreing process through the factory's reference to the scorpion's death score command
		ScorpionFactory::SendDeathCommandForScore();

		//Mark the Scorpion for deletion by the engine
		MarkForDestroy();

		//Mark the Scorpion as dead
		this->SetLifeState(GameObject::DEAD);
	}
}

void Scorpion::Destroy()
{
	ConsoleMsg::WriteLine("Deleted Scorpion!");
	DeregisterCollision<Scorpion>(*this);
}

void Scorpion::SetMyPos(sf::Vector2f _newPos)
{
	Pos = _newPos;
}

sf::Vector2f Scorpion::GetMyPos()
{
	return Pos;
}

ScorpionMover* Scorpion::GetMyMover()
{
	return myMoverRef;
}

int Scorpion::GetMyRow()
{
	return ScorpionRow;
}

void Scorpion::SetMyRow(int newRow)
{
	ScorpionRow = newRow;
}

void Scorpion::SetMyCol(int newCol)
{
	ScorpionCol = newCol;
}

int Scorpion::GetMyCol()
{
	return ScorpionCol;
}