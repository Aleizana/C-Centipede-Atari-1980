// ExplosionFactory
// Andre Berthiaume, April 2013

#include "ExplosionFactory.h"
#include "TEAL\CommonElements.h"
#include "ExplosionObjectPool.h"
#include "ScoreDisplayOnDeathObjectPool.h"
#include "Explosion.h"

ExplosionFactory* ExplosionFactory::ptrInstance = nullptr;

void ExplosionFactory::privCreateExplosion1By1(sf::Vector2f pos, bool plrDeath)
{
	//Create a new Explosion from the pool
	ExplosionRef = myExplosionPool.GetExplosion();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	ExplosionRef->SetExternalManagement(RecycleExplosion);

	//Initialize the new Explosion
	ExplosionRef->Initialize(pos, scalar1By1, plrDeath);
}

void ExplosionFactory::privCreateExplosion2By1(sf::Vector2f pos, bool plrDeath)
{
	//Create a new Explosion from the pool
	ExplosionRef = myExplosionPool.GetExplosion();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	ExplosionRef->SetExternalManagement(RecycleExplosion);

	//Initialize the new Explosion and tell it to notify the game manager that the player has died once it completed
	ExplosionRef->Initialize(pos, plrDeath);
}

void ExplosionFactory::privRecycleExplosion(GameObject* _ExplosionRef)
{
	myExplosionPool.ReturnExplosion(static_cast<Explosion*>(_ExplosionRef));
}

void ExplosionFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}
