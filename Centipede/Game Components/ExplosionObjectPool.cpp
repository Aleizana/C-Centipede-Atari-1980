#include "ExplosionObjectPool.h"
#include "TEAL\CommonElements.h"
#include "Explosion.h"

ExplosionObjectPool::ExplosionObjectPool()
{
	// Alterninatively: pre-load the recycledItems queue is a few Explosions already
}

ExplosionObjectPool::~ExplosionObjectPool()
{
	// forcefully delele all recycled gameobjects

	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " Explosions");
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}

Explosion* ExplosionObjectPool::GetExplosion()
{
	Explosion* b;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New Explosion"); // For illustration purposes

		b = new Explosion();
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Explosion"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	return b;
}

void ExplosionObjectPool::ReturnExplosion(Explosion* b)
{
	recycledItems.push(static_cast<Explosion*>(b));

	// For illustration purposes
	ConsoleMsg::WriteLine("Explosion Recycled Stack Size: " + Tools::ToString(recycledItems.size()));

}