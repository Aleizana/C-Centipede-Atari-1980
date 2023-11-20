// BlasterFactory
// Andre Berthiaume, April 2013

#include "BlasterFactory.h"
#include "TEAL\CommonElements.h"
#include "BlasterObjectPool.h"
#include "Blaster.h"
#include "ControllerBase.h"
#include "SoundManager.h"
#include "GameManager.h"
#include "SoundCommand.h"
#include "PlaySoundCommand.h"

BlasterFactory* BlasterFactory::ptrInstance = nullptr;

BlasterFactory::BlasterFactory()
	: pSound(nullptr)
{

}

Blaster* BlasterFactory::privCreateBlaster(ControllerBase* _ctrlRef)
{
	//Else continue creating a new blaster from the pool
	Blaster* blasterRef = myBlasterPool.GetBlaster();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	blasterRef->SetExternalManagement(RecycleBlaster);

	//Initialize the new blaster
	blasterRef->Initialize(blasterSpawnPos, _ctrlRef);

	return blasterRef;
}

void BlasterFactory::privRecycleBlaster(GameObject* _blasterRef)
{
	myBlasterPool.ReturnBlaster(static_cast<Blaster*>(_blasterRef));
}

void BlasterFactory::Terminate()
{
	delete Instance().pSound;

	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}

sf::Vector2f BlasterFactory::privSetBlasterSpawnPos()
{
	return blasterSpawnPos;
}

void BlasterFactory::privSendDeathSoundCommand()
{
	GameManager::GetSoundManager()->SendSoundCmd(pSound);
}

void BlasterFactory::privStoreSoundCommand()
{
	pSound = GameManager::GetSoundManager()->GetSoundCommand(GameManager::GetSoundManager()->SoundEvents::BlasterDeath);
}

float BlasterFactory::privGetBlasterSpeed()
{
	return BlasterSpeedRef;
}
