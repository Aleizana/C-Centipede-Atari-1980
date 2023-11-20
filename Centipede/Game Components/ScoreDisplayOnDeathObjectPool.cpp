#include "ScoreDisplayOnDeathObjectPool.h"
#include "TEAL\CommonElements.h"
#include "ScoreDisplayOnDeath.h"

ScoreDisplayOnDeathObjectPool::ScoreDisplayOnDeathObjectPool()
{
	// Alterninatively: pre-load the recycledItems queue is a few ScoreDisplayOnDeaths already
}

ScoreDisplayOnDeathObjectPool::~ScoreDisplayOnDeathObjectPool()
{
	// forcefully delele all recycled gameobjects

	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " ScoreDisplayOnDeaths");
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}

ScoreDisplayOnDeath* ScoreDisplayOnDeathObjectPool::GetScoreDisplayOnDeath()
{
	ScoreDisplayOnDeath* b;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New ScoreDisplayOnDeath"); // For illustration purposes

		b = new ScoreDisplayOnDeath();
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled ScoreDisplayOnDeath"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	return b;
}

void ScoreDisplayOnDeathObjectPool::ReturnScoreDisplayOnDeath(ScoreDisplayOnDeath* b)
{
	recycledItems.push(static_cast<ScoreDisplayOnDeath*>(b));

	// For illustration purposes
	ConsoleMsg::WriteLine("ScoreDisplayOnDeath Recycled Stack Size: " + Tools::ToString(recycledItems.size()));

}