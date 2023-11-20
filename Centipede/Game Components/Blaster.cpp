#include "Blaster.h"
#include "Dart.h"
#include "BlasterFactory.h"
#include "Mushroom.h"
#include "ControllerBase.h"
#include "CentipedeHead.h"
#include "PlayerManager.h"
#include "DisplayOnDeathFactory.h"
#include "Player.h"
#include "GameManager.h"

Blaster::Blaster()
{
	//Initialize the player movement zone limits
	playerAreaLimit = (float)GameManager::GetPlayerMgr()->GetPlayerAreaLimit();

	//Initialize the sprite and attach it to the blaster
	BlasterSprite = sf::Sprite(ResourceManager::GetTexture("blaster"));
	BlasterSprite.setOrigin((float)BlasterSprite.getTextureRect().width, (float)BlasterSprite.getTextureRect().height);

	bitmap = ResourceManager::GetTextureBitmap("blaster");

	SetCollider(BlasterSprite, bitmap, true);

	SetDrawOrder(blasterDrawOrder);

	
}

void Blaster::Initialize(sf::Vector2f p, ControllerBase* _ctrlMgrRef)
{
	Pos = p;

	BlasterSprite.setPosition(Pos);

	//Store a reference to the specified controller
	plrCtrlRef = _ctrlMgrRef;

	impulse = sf::Vector2f(0, 0);

	//Set the state of the blaster to be living
	this->SetLifeState(GameObject::ALIVE);

	RegisterCollision<Blaster>(*this);

	RegisterInput(InputFlags::KeyPressed); // Recieve single-presses events
}

void Blaster::Destroy()
{
	//DeregisterInput();
	DeregisterCollision<Blaster>(*this);

	DeregisterInput();
}

void Blaster::KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey)
{
	plrCtrlRef->KeyPressed(this, k, altKey, ctrlKey, shiftKey, systemKey);
}

void Blaster::Update()
{
	//Attach the sprite to the blaster as it moves, and limit the range that the blaster can move
	Tools::Clamp<float>(Pos.x, (float)BlasterSprite.getTextureRect().width, WindowManager::Window().getView().getSize().x);
	//Player movement zone config
	Tools::Clamp<float>(Pos.y, playerAreaLimit, WindowManager::Window().getView().getSize().y);

	plrCtrlRef->Update(impulse, this);
	
	//Update the position of the sprite to match the blaster object
	BlasterSprite.setPosition(Pos);

}


void Blaster::Draw()
{
	WindowManager::Window().draw(BlasterSprite);
}

void Blaster::Collision(Mushroom* other)
{
	//Make it so that whatever direction the player is trying to move through the mushroom will be reversed
	Pos -= impulse;
}

void Blaster::Collision(Flea* other)
{
	//Set the blaster to be dead
	this->SetLifeState(GameObject::DEAD);

	BlasterFactory::SendDeathSoundCommand();

	//Create an explosion at the blaster pos
	DisplayOnDeathFactory::CreateExplosionPlayerDeath(Pos);

	//When the blaster collides with a Flea, it 'dies'
	MarkForDestroy();

	

	//GameManager::NotifyPlayerDeath();

	
}

void Blaster::Collision(CentipedeHead* other)
{
	//Set the blaster to be dead
	this->SetLifeState(GameObject::DEAD);

	BlasterFactory::SendDeathSoundCommand();

	//Create an explosion at the blaster pos
	DisplayOnDeathFactory::CreateExplosionPlayerDeath(Pos);

	//When the blaster collides with a Flea, it 'dies'
	MarkForDestroy();

	

	//GameManager::NotifyPlayerDeath();
}

//Kills the blaster and tells the factory to spawn another
void Blaster::Collision(CentipedeBody* other)
{
	//Set the blaster to be dead
	this->SetLifeState(GameObject::DEAD);

	BlasterFactory::SendDeathSoundCommand();

	//Create an explosion at the blaster pos
	DisplayOnDeathFactory::CreateExplosionPlayerDeath(Pos);

	//When the blaster collides with a Flea, it 'dies'
	MarkForDestroy();

	

	

	//GameManager::NotifyPlayerDeath();
}

//Kills the blaster and tells the factory to spawn another
void Blaster::Collision(Spider* other)
{
	//Set the blaster to be dead
	this->SetLifeState(GameObject::DEAD);

	BlasterFactory::SendDeathSoundCommand();

	//Create an explosion at the blaster pos
	DisplayOnDeathFactory::CreateExplosionPlayerDeath(Pos);

	//When the blaster collides with a Flea, it 'dies'
	MarkForDestroy();

	

	

	//GameManager::NotifyPlayerDeath();

	
}

void Blaster::MoveBlaster(sf::Vector2f _inputOffset)
{
	impulse += _inputOffset;
	Pos += _inputOffset;
}

void Blaster::SetImpulse(float x_val, float y_val)
{
	impulse.x = x_val;
	impulse.y = y_val;
}

sf::Vector2f Blaster::GetPos()
{
	return Pos;
}

void Blaster::SetPos(sf::Vector2f newPos)
{
	Pos = newPos;
}
