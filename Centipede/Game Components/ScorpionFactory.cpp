// ScorpionFactory
// Andre Berthiaume, April 2013

#include "ScorpionFactory.h"
#include "TEAL\CommonElements.h"
#include "ScorpionObjectPool.h"
#include "Scorpion.h"
#include "ScorpionMover.h"
#include "ScoreManager.h"
#include "CmdScore.h"
#include "SoundManager.h"
#include "LoopSoundCommand.h"
#include "GameManager.h"
#include "SoundCommand.h"

ScorpionFactory* ScorpionFactory::ptrInstance = nullptr;

ScorpionFactory::ScorpionFactory()
{
	//Get the scorpion death score command from the score manager
	ConsoleMsg::WriteLine("Scorpion Factory:: Getting Scorpion Death Score Command");
	pDeath = GameManager::GetScoreMgr()->GetScoreCommand(GameManager::GetScoreMgr()->ScoreEvents::ScorpionKilled);

	scorpionCount = 0;

	scorpMoverRef = new ScorpionMover();
}

void ScorpionFactory::privCreateScorpion(sf::Vector2f pos, int row, int col, ScorpionMoveBaseState* setDir)
{
	Scorpion* ScorpionRef;

	ScorpionRef = myScorpionPool.GetScorpion();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	ScorpionRef->SetExternalManagement(RecycleScorpion);

	//Initialize the new Scorpion
	ScorpionRef->Initialize(pos, scorpMoverRef, setDir);

	ScorpionRef->SetRowCol(row, col);

	scorpionCount++;

	privSendSoundCommand();

	
}

void ScorpionFactory::privRecycleScorpion(GameObject* _ScorpionRef)
{
	myScorpionPool.ReturnScorpion(static_cast<Scorpion*>(_ScorpionRef));

	//if (!GameManager::MainSceneProcessing())
	//{
	//	scorpionCount--;
	//
	//	//if there are no scorpions alive, stop the sound effect
	//	if (scorpionCount == 0)
	//	{
	//		//Use a static cast to call the Loop Sound function to stop the loop now that the scorpion is dead
	//		static_cast<LoopSoundCommand*>(pSound)->StopLoop();
	//	}
	//}

	
}

void ScorpionFactory::privSendDeathCommandForScore()
{
	//Pass the score command to the manager so that it can create a command score instance
	GameManager::GetScoreMgr()->SendScoreCmd(pDeath);
}

void ScorpionFactory::Terminate()
{
	//Delete the score command
	delete Instance().pDeath;
	delete Instance().pSound;
	delete Instance().scorpMoverRef;

	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}

void ScorpionFactory::privSetScorpSpeed(float scorpSpeed)
{
	//scorpionSpeed = scorpSpeed;

	scorpMoverRef->SetScorpionSpeed(scorpSpeed);
}

void ScorpionFactory::privSendSoundCommand()
{
	GameManager::GetSoundManager()->SendSoundCmd(pSound);
	
}

void ScorpionFactory::privStoreSoundCommand()
{
	pSound = GameManager::GetSoundManager()->GetSoundCommand(GameManager::GetSoundManager()->SoundEvents::ScorpionLoop);
}

void ScorpionFactory::privStopLoop()
{
	//if there are no scorpions alive, stop the sound effect
	if (scorpionCount == 0)
	{
		//Use a static cast to call the Loop Sound function to stop the loop now that the scorpion is dead
		static_cast<LoopSoundCommand*>(pSound)->StopLoop();
	}
}

void ScorpionFactory::privDecrementScorpCount()
{
	scorpionCount--;
}
