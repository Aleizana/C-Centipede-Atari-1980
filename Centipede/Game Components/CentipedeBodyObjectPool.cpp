#include "CentipedeBodyObjectPool.h"
#include "TEAL\CommonElements.h"
#include "CentipedeBody.h"

CentipedeBodyObjectPool::CentipedeBodyObjectPool()
{
	// Alterninatively: pre-load the recycledItems queue is a few CentipedeBodys already
}

CentipedeBodyObjectPool::~CentipedeBodyObjectPool()
{
	// forcefully delele all recycled gameobjects

	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " CentipedeBodys");
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}

CentipedeBody* CentipedeBodyObjectPool::GetCentipedeBody()
{
	CentipedeBody* b;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New CentipedeBody"); // For illustration purposes

		b = new CentipedeBody();
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled CentipedeBody"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	return b;
}

void CentipedeBodyObjectPool::ReturnCentipedeBody(CentipedeBody* b)
{
	recycledItems.push(static_cast<CentipedeBody*>(b));

	// For illustration purposes
	ConsoleMsg::WriteLine("Recycled Centipede Body Stack Size: " + Tools::ToString(recycledItems.size()));

}