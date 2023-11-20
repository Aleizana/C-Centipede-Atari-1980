#include "DartObjectPool.h"
#include "TEAL\CommonElements.h"
#include "Dart.h"

DartObjectPool::DartObjectPool()
{
	// Alterninatively: pre-load the recycledItems queue is a few Darts already
}

DartObjectPool::~DartObjectPool()
{
	// forcefully delele all recycled gameobjects

	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " Darts");
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}

Dart* DartObjectPool::GetDart()
{
	Dart* b;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New Dart"); // For illustration purposes

		b = new Dart();
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Dart"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	return b;
}

void DartObjectPool::ReturnDart(Dart* b)
{
	recycledItems.push(static_cast<Dart*>(b));

	// For illustration purposes
	ConsoleMsg::WriteLine("Dart Recycled Stack Size: " + Tools::ToString(recycledItems.size()));

}