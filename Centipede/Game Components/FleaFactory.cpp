// FleaFactory
// Andre Berthiaume, April 2013

#include "FleaFactory.h"
#include "TEAL\CommonElements.h"
#include "FleaObjectPool.h"
#include "Flea.h"
#include "FleaMover.h"
#include "ScoreManager.h"
#include "CmdScore.h"
#include "SoundManager.h"
#include "SoundCommand.h"
#include "GameManager.h"

FleaFactory* FleaFactory::ptrInstance = nullptr;

FleaFactory::FleaFactory()
{
	//Get the Flea death score command from the score manager
	ConsoleMsg::WriteLine("Flea Factory:: Getting Flea Death Score Command");
	pDeath = GameManager::GetScoreMgr()->GetScoreCommand(GameManager::GetScoreMgr()->ScoreEvents::FleaKilled);

	chanceToTriggerMushSpawn = defaultIfChanceToTriggerIsZero;

	fleaMoverRef = new FleaMover();
}

void FleaFactory::privCreateFlea(sf::Vector2f pos, int row, int col)
{
	Flea* fleaRef;

	fleaRef = myFleaPool.GetFlea();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	fleaRef->SetExternalManagement(RecycleFlea);

	//Initialize the new Flea
	fleaRef->Initialize(pos, fleaMoverRef);

	fleaRef->SetRowCol(row, col);


	privSendSoundCommand();
}

void FleaFactory::privRecycleFlea(GameObject* _FleaRef)
{
	myFleaPool.ReturnFlea(static_cast<Flea*>(_FleaRef));

	
}

void FleaFactory::Terminate()
{
	//Delete the score command
	delete Instance().pDeath;
	delete Instance().pSound;
	delete Instance().fleaMoverRef;

	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}

void FleaFactory::privSendDeathCommandForScore()
{
	//Pass the score command to the manager so that it can create a command score instance
	GameManager::GetScoreMgr()->SendScoreCmd(pDeath);
}

void FleaFactory::privSendSoundCommand()
{
	GameManager::GetSoundManager()->SendSoundCmd(pSound);
}

void FleaFactory::privStoreSoundCommand()
{
	pSound = GameManager::GetSoundManager()->GetSoundCommand(GameManager::GetSoundManager()->SoundEvents::FleaFall);
}

void FleaFactory::privSetChanceToTriggerMushSpawn(int setNum)
{
	if (setNum == 0)
	{
		chanceToTriggerMushSpawn = defaultIfChanceToTriggerIsZero;
	}
	else
	{
		chanceToTriggerMushSpawn = setNum;
	}
	
}

int FleaFactory::privGetChanceToTriggerMushSpawn()
{
	return chanceToTriggerMushSpawn;
}
