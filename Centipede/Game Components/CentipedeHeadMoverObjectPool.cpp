#include "CentipedeHeadMoverObjectPool.h"
#include "TEAL\CommonElements.h"
#include "CentipedeHeadMover.h"

CentipedeHeadMoverObjectPool::CentipedeHeadMoverObjectPool()
{
	// Alterninatively: pre-load the recycledItems queue is a few CentipedeHeads already
}

CentipedeHeadMoverObjectPool::~CentipedeHeadMoverObjectPool()
{
	// forcefully delele all recycled gameobjects

	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " CentipedeHeadMovers");
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}

CentipedeHeadMover* CentipedeHeadMoverObjectPool::GetCentipedeHeadMover()
{
	CentipedeHeadMover* b;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New CentipedeHead Mover"); // For illustration purposes

		b = new CentipedeHeadMover();
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled CentipedeHead Mover"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		//b->RegisterToCurrentScene();
	}

	return b;
}

void CentipedeHeadMoverObjectPool::ReturnCentipedeHeadMover(CentipedeHeadMover* b)
{
	recycledItems.push(static_cast<CentipedeHeadMover*>(b));

	// For illustration purposes
	ConsoleMsg::WriteLine("CentipedeHead Mover Recycled Stack Size: " + Tools::ToString(recycledItems.size()));

}