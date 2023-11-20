#include "BlasterObjectPool.h"
#include "TEAL\CommonElements.h"
#include "Blaster.h"

BlasterObjectPool::BlasterObjectPool()
{
	// Alterninatively: pre-load the recycledItems queue is a few Blasters already
}

BlasterObjectPool::~BlasterObjectPool()
{
	// forcefully delele all recycled gameobjects

	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " Blasters");
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}

Blaster* BlasterObjectPool::GetBlaster()
{
	Blaster* b;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New Blaster"); // For illustration purposes

		b = new Blaster();
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Blaster"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	return b;
}

void BlasterObjectPool::ReturnBlaster(Blaster* b)
{
	recycledItems.push(static_cast<Blaster*>(b));

	// For illustration purposes
	ConsoleMsg::WriteLine("Blaster Recycled Stack Size: " + Tools::ToString(recycledItems.size()));

}