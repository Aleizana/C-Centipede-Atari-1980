// DisplayOnDeathFactory
// Andre Berthiaume, April 2013

#include "DisplayOnDeathFactory.h"
#include "TEAL\CommonElements.h"
#include "ExplosionObjectPool.h"
#include "ScoreDisplayOnDeathObjectPool.h"
#include "Explosion.h"
#include "ScoreDisplayOnDeath.h"
#include "SoundManager.h"
#include "GameManager.h"
#include "SoundCommand.h"

DisplayOnDeathFactory* DisplayOnDeathFactory::ptrInstance = nullptr;

DisplayOnDeathFactory::DisplayOnDeathFactory()
	: pDeathSound(nullptr)
{
}

void DisplayOnDeathFactory::privCreateExplosion1By1(sf::Vector2f pos, bool plrDeath)
{
	//Create a new Explosion from the pool
	Explosion* ExplosionRef = myExplosionPool.GetExplosion();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	ExplosionRef->SetExternalManagement(RecycleExplosion);

	//Initialize the new Explosion
	ExplosionRef->Initialize(pos, plrDeath, scalar1By1);
}

void DisplayOnDeathFactory::privCreateExplosion2By1(sf::Vector2f pos, bool plrDeath)
{
	//Create a new Explosion from the pool
	Explosion* ExplosionRef = myExplosionPool.GetExplosion();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	ExplosionRef->SetExternalManagement(RecycleExplosion);

	//Initialize the new Explosion and tell it to notify the game manager that the player has died once it completed
	ExplosionRef->Initialize(pos, plrDeath);
}

void DisplayOnDeathFactory::privCreateScoreDisplayOnSpiderDeath(sf::Vector2f pos, int score)
{
	ScoreDisplayOnDeath* scoreDisplayRef = myScoreDisplayPool.GetScoreDisplayOnDeath();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	scoreDisplayRef->SetExternalManagement(RecycleScoreDisplay);

	//Initialize the new scoreDisplayRef and tell it to notify the game manager that the player has died once it completed
	scoreDisplayRef->InitializeWithScore(pos, score);
}

void DisplayOnDeathFactory::privRecycleExplosion(GameObject* _ExplosionRef)
{
	myExplosionPool.ReturnExplosion(static_cast<Explosion*>(_ExplosionRef));
}

void DisplayOnDeathFactory::privRecycleScoreDisplay(GameObject* _ScoreDisplayRef)
{
	myScoreDisplayPool.ReturnScoreDisplayOnDeath(static_cast<ScoreDisplayOnDeath*>(_ScoreDisplayRef));
}

void DisplayOnDeathFactory::privStoreSoundCommand()
{
	pDeathSound = GameManager::GetSoundManager()->GetSoundCommand(SoundManager::SoundEvents::NonPlayerDeath);
}

void DisplayOnDeathFactory::privSendSoundCommand()
{
	GameManager::GetSoundManager()->SendSoundCmd(pDeathSound);
}

void DisplayOnDeathFactory::Terminate()
{
	delete ptrInstance->pDeathSound;

	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}
