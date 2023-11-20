#include "ScorpionObjectPool.h"
#include "TEAL\CommonElements.h"
#include "Scorpion.h"

ScorpionObjectPool::ScorpionObjectPool()
{
	// Alterninatively: pre-load the recycledItems queue is a few Scorpions already
}

ScorpionObjectPool::~ScorpionObjectPool()
{
	// forcefully delele all recycled gameobjects

	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " Scorpions");
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}

Scorpion* ScorpionObjectPool::GetScorpion()
{
	Scorpion* b;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New Scorpion"); // For illustration purposes

		b = new Scorpion();
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Scorpion"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	return b;
}

void ScorpionObjectPool::ReturnScorpion(Scorpion* b)
{
	recycledItems.push(static_cast<Scorpion*>(b));

	// For illustration purposes
	ConsoleMsg::WriteLine("Recycled Scorpion Stack Size: " + Tools::ToString(recycledItems.size()));

}