#include "CentipedeHeadObjectPool.h"
#include "TEAL\CommonElements.h"
#include "CentipedeHead.h"

CentipedeHeadObjectPool::CentipedeHeadObjectPool()
{
	// Alterninatively: pre-load the recycledItems queue is a few CentipedeHeads already
}

CentipedeHeadObjectPool::~CentipedeHeadObjectPool()
{
	// forcefully delele all recycled gameobjects

	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " CentipedeHeads");
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}

CentipedeHead* CentipedeHeadObjectPool::GetCentipedeHead()
{
	CentipedeHead* b;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New CentipedeHead"); // For illustration purposes

		b = new CentipedeHead();
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled CentipedeHead"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	return b;
}

void CentipedeHeadObjectPool::ReturnCentipedeHead(CentipedeHead* b)
{
	recycledItems.push(static_cast<CentipedeHead*>(b));

	// For illustration purposes
	ConsoleMsg::WriteLine("Recycled Centipede Head Stack Size: " + Tools::ToString(recycledItems.size()));

}