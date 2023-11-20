#include "Dart.h"
#include "Scorpion.h"
#include "Flea.h"
#include "CentipedeBody.h"
#include "CentipedeHead.h"

Dart::Dart()
{
	bitmap = ResourceManager::GetTextureBitmap("bullet");
	DartSprite = sf::Sprite(ResourceManager::GetTexture("bullet"));

	//Set the (0,0) position for the sprite
	DartSprite.setOrigin((float)DartSprite.getTextureRect().width, (float)DartSprite.getTextureRect().height);

	SetCollider(DartSprite, bitmap);
}

void Dart::Initialize(sf::Vector2f p)
{
	Pos = p;
	RegisterCollision<Dart>(*this);

	//Set the state of the dart to be 'alive' 
	this->SetLifeState(GameObject::ALIVE);
}

void Dart::Update()
{
	//Moves the dart upwards from the blaster
	Pos.y -= dartSpeedConst;

	//If the dart crosses the top-of-screen threshold, destroy it
	if (Pos.y < dartYThreshold)
	{
		MarkForDestroy();

		//Set the state of the blaster to dead
		this->SetLifeState(GameObject::DEAD);

		ConsoleMsg::WriteLine("Bullet off-screen! Ship can fire again!");
	}
		

	//Update the position of the sprite of the bullet as it moves
	DartSprite.setPosition(Pos);
}

void Dart::Draw()
{
	WindowManager::Window().draw(DartSprite);
}

void Dart::Destroy()
{
	ConsoleMsg::WriteLine("Deleted dart!");
	DeregisterCollision<Dart>(*this);
	this->myState = GameObject::DEAD;
}

void Dart::Collision(Mushroom* other)
{
	

	//Mark this object as dead
	this->SetLifeState(GameObject::DEAD);

	ConsoleMsg::WriteLine("Dart + mushroom collision -> Ship can fire again!");
}

void Dart::Collision(Flea* other)
{

	//Mark this object as dead
	this->SetLifeState(GameObject::DEAD);

	ConsoleMsg::WriteLine("Dart + flea collision -> Ship can fire again!");
}

void Dart::Collision(Scorpion* other)
{

	//Mark this object as dead
	this->SetLifeState(GameObject::DEAD);

	ConsoleMsg::WriteLine("Dart + scorpion collision -> Ship can fire again!");
}

void Dart::Collision(CentipedeHead* other)
{

	//Mark this object as dead
	this->SetLifeState(GameObject::DEAD);

	ConsoleMsg::WriteLine("Dart + scorpion collision -> Ship can fire again!");
}

void Dart::Collision(CentipedeBody* other)
{

	//Mark this object as dead
	this->SetLifeState(GameObject::DEAD);

	ConsoleMsg::WriteLine("Dart + scorpion collision -> Ship can fire again!");
}

void Dart::Collision(Spider* other)
{
	//Mark this object as dead
	this->SetLifeState(GameObject::DEAD);

	ConsoleMsg::WriteLine("Dart + spider collision -> Ship can fire again!");
}

void Dart::Collision(Glyph* other)
{
	//Mark this object as dead
	this->SetLifeState(GameObject::DEAD);

	ConsoleMsg::WriteLine("Dart + Glyph collision -> Ship can fire again!");

	
}
