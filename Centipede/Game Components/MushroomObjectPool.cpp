#include "MushroomObjectPool.h"
#include "TEAL\CommonElements.h"
#include "Mushroom.h"

MushroomObjectPool::MushroomObjectPool()
{
	// Alterninatively: pre-load the recycledItems queue is a few Mushrooms already
}

MushroomObjectPool::~MushroomObjectPool()
{
	// forcefully delele all recycled gameobjects

	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " Mushrooms");
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}

Mushroom* MushroomObjectPool::GetMushroom()
{
	Mushroom* b;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New Mushroom"); // For illustration purposes

		b = new Mushroom();
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Mushroom"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	return b;
}

void MushroomObjectPool::ReturnMushroom(Mushroom* b)
{
	recycledItems.push(static_cast<Mushroom*>(b));

	// For illustration purposes
	ConsoleMsg::WriteLine("Mushroom Recycled Stack Size: " + Tools::ToString(recycledItems.size()));

}