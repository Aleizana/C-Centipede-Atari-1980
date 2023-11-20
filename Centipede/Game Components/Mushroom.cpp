// Mushroom
// // Andre Berthiaume, March 2013

#include "Mushroom.h"
#include <math.h>
#include "PlayerManager.h"
#include "Player.h"
#include "Grid.h"
#include "Dart.h"
#include "Mushroom.h"
#include "MushroomFactory.h"
#include "DisplayOnDeathFactory.h"
#include "GameManager.h"
#include "MushroomState.h"
#include "MushroomPoisonedState.h"
#include "MushroomNormalState.h"

Mushroom::Mushroom()
{
	pCurrState = (MushroomState*)&MushroomState::normalState;

	sf::IntRect spriteRect = pCurrState->GetSpriteRectFromState(this);

	bitmap = &ResourceManager::GetTextureBitmap("mushroom");
	MainSprite = sf::Sprite(ResourceManager::GetTexture("mushroom"), spriteRect);

	MainSprite.setOrigin(MainSprite.getTextureRect().width / spriteOriginSizeDivisor, MainSprite.getTextureRect().height / spriteOriginSizeDivisor);

	SetCollider(MainSprite, *bitmap);

	health = MushHealth;

	myType = GameObject::ObjectType::MUSHROOM;

	
}

void Mushroom::Initialize(sf::Vector2f p)
{
	Pos = p;
	RegisterCollision<Mushroom>(*this);

	//Set the state of the mushroom to be 'alive' 
	this->SetLifeState(GameObject::ALIVE);

	pCurrState = (MushroomState*)&MushroomState::normalState;

	myRow = 0;

	myCol = 0;

	health = MushHealth;

	sf::IntRect spriteRect = pCurrState->GetSpriteRectFromState(this);

	MainSprite.setTextureRect(spriteRect);
}

void Mushroom::SetRowCol(int row, int col)
{
	myRow = row;
	myCol = col;

}

void Mushroom::ActivatePoisonState()
{
	ConsoleMsg::WriteLine("Mushroom got poisoned by Scorpion!");
	pCurrState = (MushroomState*)&MushroomState::poisonedState;
	sf::IntRect spriteRect = pCurrState->GetSpriteRectFromState(this);
	MainSprite.setTextureRect(spriteRect);
	myState = GameObject::POISON;
}

void Mushroom::ResetHealth()
{
	health = MushHealth;
}

void Mushroom::Update()
{
	//You HAVE to do this every update or else the position will go to (0,0)
	MainSprite.setPosition(Pos);

}

void Mushroom::Draw()
{
	WindowManager::Window().draw(MainSprite);
}

void Mushroom::Collision(Dart* other)
{
	//Mark the dart for destroy so it can't kill anything else
	other->GameObject::MarkForDestroy();

	ConsoleMsg::WriteLine("Mushroom took damage!");

	//dmgTaken += GetDmgAmount();
	health -= GetDmgAmount();

	//Mushroom dies at damage taken == 4
	if (health <= GetDeathHP())
	{
		//Tell the state to send the correct death score command
		pCurrState->SendDeathScoreCommand();

		//Create an explosion at the mushrooms pos
		DisplayOnDeathFactory::CreateExplosion1By1(Pos);

		//Mark the mushroom for deletion by the engine
		GameObject::MarkForDestroy();

		DisplayOnDeathFactory::SendSoundCommand();

		//Mark the mushroom as dead
		this->SetLifeState(GameObject::DEAD);

		//Free up the destroyed mushroom's pos in the grid
		GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->ClearGridSpot(myRow, myCol);
	}
	//If the mushroom is still alive then update it's sprite to reflect the damage taken
	else
	{
		//pCurrState->SetSpriteFromState(this);
		sf::IntRect spriteRect = pCurrState->GetSpriteRectFromState(this);

		MainSprite.setTextureRect(spriteRect);
	}
}

void Mushroom::Collision(Spider* other)
{
	ConsoleMsg::WriteLine("Mushroom got eaten by spider!");

	//Mark the mushroom for deletion by the engine
	GameObject::MarkForDestroy();

	//Mark the mushroom as dead
	this->SetLifeState(GameObject::DEAD);

	//Free up the destroyed mushroom's pos in the grid
	GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->ClearGridSpot(myRow, myCol);
}

void Mushroom::Destroy()
{
	ConsoleMsg::WriteLine("Deleted mushroom!");
	DeregisterCollision<Mushroom>(*this);
}

const int Mushroom::GetMyRow() const
{
	return myRow;
}

const int Mushroom::GetMyCol() const
{
	return myCol;
}

void Mushroom::ResetState()
{
	//Reset the offset used to make the sprite appear poisoned
	//poisonedSpriteSheetOffset = 0;
	pCurrState = (MushroomState*)&MushroomState::normalState;

	//Reset the life state of the mushroom to be ALIVE
	myState = GameObject::LifeState::ALIVE;

	health = MushHealth;

	sf::IntRect spriteRect = pCurrState->GetSpriteRectFromState(this);

	MainSprite.setTextureRect(spriteRect);
}

sf::Vector2f Mushroom::GetPos()
{
	return Pos;
}

sf::Sprite Mushroom::GetSprite()
{
	return MainSprite;
}

const int Mushroom::GetStartingHP() const
{
	return MushHealth;
}
