#include "SpiderObjectPool.h"
#include "TEAL\CommonElements.h"
#include "Spider.h"

SpiderObjectPool::SpiderObjectPool()
{
	// Alterninatively: pre-load the recycledItems queue is a few Spiders already
}

SpiderObjectPool::~SpiderObjectPool()
{
	// forcefully delele all recycled gameobjects

	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " Spiders");
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}

Spider* SpiderObjectPool::GetSpider()
{
	Spider* b;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New Spider"); // For illustration purposes

		b = new Spider();
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Spider"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	return b;
}

void SpiderObjectPool::ReturnSpider(Spider* b)
{
	recycledItems.push(static_cast<Spider*>(b));

	// For illustration purposes
	ConsoleMsg::WriteLine("Recycled Spider Stack Size: " + Tools::ToString(recycledItems.size()));

}