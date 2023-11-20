// DartFactory
// Andre Berthiaume, April 2013

#include "DartFactory.h"
#include "TEAL\CommonElements.h"
#include "DartObjectPool.h"
#include "Dart.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "SoundCommand.h"
#include "PlaySoundCommand.h"

DartFactory* DartFactory::ptrInstance = nullptr;

DartFactory::DartFactory()
	: dartRef(nullptr), pSound(nullptr)
{
}

void DartFactory::privCreateDart(sf::Vector2f pos)
{
	//To avoid nullptr errors
	if (dartRef != nullptr)
	{
		//If the previously fired dart is still alive in-game, do not create a new one
		if (dartRef->GetLifeState() == GameObject::ALIVE)
		{
			return;
		}
	}

	//Else continue creating a new dart from the pool
	dartRef = myDartPool.GetDart();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	dartRef->SetExternalManagement(RecycleDart);

	//Initialize the new dart
	dartRef->Initialize(pos);

	privSendSoundCommand();
}

void DartFactory::privRecycleDart(GameObject* _dartRef)
{
	myDartPool.ReturnDart(static_cast<Dart*>(_dartRef));
}

void DartFactory::privSendSoundCommand()
{
	GameManager::GetSoundManager()->SendSoundCmd(pSound);
}

void DartFactory::privStoreSoundCommand()
{
	pSound = GameManager::GetSoundManager()->GetSoundCommand(GameManager::GetSoundManager()->SoundEvents::FireDart);
}

void DartFactory::Terminate()
{
	delete Instance().pSound;

	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}
