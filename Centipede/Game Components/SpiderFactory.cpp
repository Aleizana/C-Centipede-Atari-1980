// SpiderFactory
// Andre Berthiaume, April 2013

#include "SpiderFactory.h"
#include "TEAL\CommonElements.h"
#include "SpiderObjectPool.h"
#include "Spider.h"
#include "SpiderMover.h"
#include "ScoreManager.h"
#include "CmdScore.h"
#include "CmdScoreByDistance.h"
#include "SoundManager.h"
#include "LoopSoundCommand.h"
#include "SoundCommand.h"
#include "GameManager.h"
#include "MoveFSM.h"

SpiderFactory* SpiderFactory::ptrInstance = nullptr;

SpiderFactory::SpiderFactory() : 
	SpiderSpeed(0.0f), pDeath(GameManager::GetScoreMgr()->GetScoreCommand(GameManager::GetScoreMgr()->ScoreEvents::SpiderKilled)), spiderCount(0), pSound(nullptr)
{
	//Get the spider death score command from the score manager
	ConsoleMsg::WriteLine("Spider Factory: Getting Spider Death Score Command");

	//Initialize each of the array indices of the spider state array with constant values from the moveFSM file
	SpiderStateArray[0] = (SpiderMoveState*)&MoveFSM::StateSpiderMoveDownDiagLeft;
	SpiderStateArray[1] = (SpiderMoveState*)&MoveFSM::StateSpiderMoveUpDiagLeft;
	SpiderStateArray[2] = (SpiderMoveState*)&MoveFSM::StateSpiderMoveDown;
	SpiderStateArray[3] = (SpiderMoveState*)&MoveFSM::StateSpiderMoveUp;
	SpiderStateArray[4] = (SpiderMoveState*)&MoveFSM::StateSpiderMoveDownDiagRight;
	SpiderStateArray[5] = (SpiderMoveState*)&MoveFSM::StateSpiderMoveUpDiagRight;

	spiderMoverRef = new SpiderMover;
}

void SpiderFactory::privCreateSpider(sf::Vector2f pos, int row, int col, SpiderMainDirection setDir)
{

	Spider* SpiderRef;

	SpiderRef = mySpiderPool.GetSpider();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	SpiderRef->SetExternalManagement(RecycleSpider);

	//Initialize the new Spider
	SpiderRef->Initialize(pos, spiderMoverRef, setDir);

	SpiderRef->SetRowCol(row, col);

	privSendSoundCommand();

	spiderCount++;

	
}

void SpiderFactory::privRecycleSpider(GameObject* _SpiderRef)
{
	mySpiderPool.ReturnSpider(static_cast<Spider*>(_SpiderRef));

	

	spiderCount--;

	//if there are no spiders alive, stop the sound effect
	if (spiderCount == 0 && GameManager::MainSceneProcessing())
	{
		//Use a static cast to call the Loop Sound function to stop the loop now that the spider is dead
		static_cast<LoopSoundCommand*>(pSound)->StopLoop();
	}
}

void SpiderFactory::Terminate()
{
	//Delete the score command
	delete Instance().pDeath;
	delete Instance().pSound;
	delete Instance().spiderMoverRef;

	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}

float SpiderFactory::privGetSpiderSpeed()
{
	return SpiderSpeed;
}

void SpiderFactory::privSetSpiderSpeed(float spdrSpeed)
{
	spiderMoverRef->SetSpiderSpeed(spdrSpeed);
}

void SpiderFactory::privSendDeathCommandForScore(sf::Vector2f spiderPos)
{
	//Send the position of the spider so that the command can add it to the queue
	static_cast<CmdScoreByDistance*>(pDeath)->SetPos(spiderPos);

	//Pass the score command to the manager so that it can create a command score instance
	GameManager::GetScoreMgr()->SendScoreCmd(pDeath);
}

void SpiderFactory::privSendSoundCommand()
{
	GameManager::GetSoundManager()->SendSoundCmd(pSound);
	
}

void SpiderFactory::privStoreSoundCommand()
{
	pSound = GameManager::GetSoundManager()->GetSoundCommand(GameManager::GetSoundManager()->SoundEvents::SpiderLoop);
}

void SpiderFactory::privStopSpiderLoop()
{
	//Use a static cast to call the Loop Sound function to stop the loop now that the spider is dead
	static_cast<LoopSoundCommand*>(pSound)->StopLoop();
}

const SpiderMoveState* SpiderFactory::privGetSpiderState(int index)
{
	return SpiderStateArray[index];
}

const SpiderMoveState* SpiderFactory::privGetLeftDirState()
{
	return SpiderStateArray[LeftStateArrayVal];
}

const SpiderMoveState* SpiderFactory::privGetRightDirState()
{
	return SpiderStateArray[RightStateArrayVal];
}
