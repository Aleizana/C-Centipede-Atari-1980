#include "FleaObjectPool.h"
#include "TEAL\CommonElements.h"
#include "Flea.h"

FleaObjectPool::FleaObjectPool()
{
	// Alterninatively: pre-load the recycledItems queue is a few Fleas already
}

FleaObjectPool::~FleaObjectPool()
{
	// forcefully delele all recycled gameobjects

	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " Fleas");
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}

Flea* FleaObjectPool::GetFlea()
{
	Flea* b;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New Flea"); // For illustration purposes

		b = new Flea();
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Flea"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	return b;
}

void FleaObjectPool::ReturnFlea(Flea* b)
{
	recycledItems.push(static_cast<Flea*>(b));

	// For illustration purposes
	ConsoleMsg::WriteLine("Recycled Flea Stack Size: " + Tools::ToString(recycledItems.size()));

}