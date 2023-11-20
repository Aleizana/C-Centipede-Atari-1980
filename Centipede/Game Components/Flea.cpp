// Flea
// // Andre Berthiaume, March 2013

#include "Flea.h"
#include <math.h>
#include "Grid.h"
#include "FleaMover.h"
#include "FleaFactory.h"
#include "Dart.h"
#include "DisplayOnDeathFactory.h"
#include "GameManager.h"

Flea::Flea()
{
	bitmap = &ResourceManager::GetTextureBitmap("flea");

	//Frame count width is the width of the sprite sheet divided by the number of diff sprites you have in the row
	//Frame count height is the height of the sprite sheet divided by the number of diff sprites you have in the column
	//Frames per second is the speed at which you will cycle through the sprites
	FleaSprite = AnimatedSprite(ResourceManager::GetTexture("flea"), fleaFrameCountWidth, fleaFrameCountHeight, fleaSpriteFPS);

	//Sets the first and the last frame of the sprite sheet
	FleaSprite.SetAnimation(fleaSpriteFirstFrame, fleaSpriteLastFrame);

	//Set the origin (0,0) of the sprite
	FleaSprite.setOrigin(FleaSprite.getTextureRect().width / spriteOriginSizeDivisor, FleaSprite.getTextureRect().height / spriteOriginSizeDivisor);

	//Set and register flea collision
	SetCollider(FleaSprite, *bitmap);
}

void Flea::Initialize(sf::Vector2f p, FleaMover* _moverRef)
{
	Pos = p;

	RegisterCollision<Flea>(*this);

	myMoverRef = _moverRef;

	//Initialize game variables of the flea
	this->SetLifeState(GameObject::ALIVE);
	health = FleaSpawnHealth;
	fleaRow = 0;
	fleaCol = 0;
	countMovement = 0;
	currSpeed = myMoverRef->GetBaseFleaSpeed();
}

void Flea::SetRowCol(int row, int col)
{
	fleaRow = row;
	fleaCol = col;
}

void Flea::Update()
{
	//Handle updating the position of the flea
	myMoverRef->HandleFleaMove(this, countMovement, GameManager::GetGridMgr()->GetPixelDistance());

	//You HAVE to do this every update or else the position will go to (0,0)
	FleaSprite.setPosition(Pos);

	//Update the appearance of the sprite
	FleaSprite.Update();

	
}

void Flea::Draw()
{
	WindowManager::Window().draw(FleaSprite);
}

void Flea::Collision(Dart* other)
{
	//Mark the dart for destroy so it can't destroy anything else
	other->GameObject::MarkForDestroy();

	//Reduce the health of the Flea
	health -= GetDmgAmount();

	//Flea dies at health <= 0
	if (health <= GetDeathHP())
	{
		DisplayOnDeathFactory::SendSoundCommand();

		//Create an explosion at the fleas pos
		DisplayOnDeathFactory::CreateExplosion1By1(Pos);

		//When the flea dies by the player's dart, tell the factory to send the score command to the score manager
		FleaFactory::SendDeathCommandForScore();

		//Mark the Flea for deletion by the engine
		GameObject::MarkForDestroy();

		//Mark the Flea as dead
		this->SetLifeState(GameObject::DEAD);
	}
	//Increase the speed of the flea by a multiplier once it has been damaged once
	else if (health != FleaSpawnHealth)
	{
		//The mover will increase the speed of the flea
		myMoverRef->HandleFleaDamage(this);
	}
}

void Flea::Destroy()
{
	//Recycle the flea's mover ref, as it is not a game object and would not return automatically
	//FleaFactory::RecycleFleaMover(myMoverRef);

	ConsoleMsg::WriteLine("Deleted Flea!");
	DeregisterCollision<Flea>(*this);
}

void Flea::SetMyPos(sf::Vector2f _newPos)
{
	Pos = _newPos;
}

sf::Vector2f Flea::GetMyPos()
{
	return Pos;
}

int Flea::GetMyHealth()
{
	return health;
}

float Flea::GetSpeed()
{
	return currSpeed;
}

void Flea::SetSpeedThroughMulitplier(float multiplier)
{
	currSpeed *= multiplier;
}

int Flea::GetMyRow()
{
	return fleaRow;
}

void Flea::SetMyRow(int newRow)
{
	fleaRow = newRow;
}

int Flea::GetMyCol()
{
	return fleaCol;
}