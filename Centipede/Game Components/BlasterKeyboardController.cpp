#include "BlasterKeyboardController.h"
#include "Blaster.h"
#include "DartFactory.h"
#include "PlayerManager.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "BlasterFactory.h"

BlasterKeyboardController::BlasterKeyboardController()
	: inputOffset(0.0f)
{
}

void BlasterKeyboardController::Initialize()
{
	inputOffset = BlasterFactory::GetBlasterSpeed();
}

void BlasterKeyboardController::Update(sf::Vector2f& impulse, Blaster* playerRef)
{
	//Set the impulse val of the blaster to be 0 so that it only moves while keys are pressed
	playerRef->SetImpulse(ImpulseReset, ImpulseReset);

	//Locally set impulse so that the ship will only move while movement inputs are detected
	impulse.x = ImpulseReset;
	impulse.y = ImpulseReset;

	//Offset applied by player input
	float inputOffset = BlasterFactory::GetBlasterSpeed();

	// Continuous key-down tests for arrow keys
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		impulse += sf::Vector2f(-inputOffset, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		impulse += sf::Vector2f(inputOffset, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		impulse += sf::Vector2f(0, -inputOffset);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		impulse += sf::Vector2f(0, inputOffset);
	}

	playerRef->MoveBlaster(impulse);
	
}

void BlasterKeyboardController::KeyPressed(Blaster* playerRef, sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey)
{
	//If enter is pressed and the blaster is able to fire
	if (k == sf::Keyboard::Return)
	{
		ConsoleMsg::WriteLine("Pew! Pew!");

		//Tell the dart factory to create a dart at the blaster's position
		DartFactory::CreateDart(playerRef->GetPos());

		
	}
	//Mutes/Unmutes the game when pressed
	else if (k == sf::Keyboard::M)
	{
		GameManager::GetSoundManager()->ToggleMute();
	}
}