// CentipedeBodyFactory
// Andre Berthiaume, April 2013

#include "CentipedeBodyFactory.h"
#include "TEAL\CommonElements.h"
#include "CentipedeBodyObjectPool.h"
#include "CentipedeBody.h"
#include "Grid.h"
#include "MovementCollection.h"
#include "CentipedeHead.h"
#include "ScoreManager.h"
#include "CmdScore.h"
#include "GameManager.h"

CentipedeBodyFactory* CentipedeBodyFactory::ptrInstance = nullptr;

CentipedeBodyFactory::CentipedeBodyFactory()
{
	//Get the CentipedeBody death score command from the score manager
	ConsoleMsg::WriteLine("CentipedeBody Factory:: Getting CentipedeBody Death Score Command");
	pDeath = GameManager::GetScoreMgr()->GetScoreCommand(GameManager::GetScoreMgr()->ScoreEvents::CentipedeBodyKilled);

	//Set the number of centipede bodies to be 0
	bodyCount = 0;
}

CentipedeBody* CentipedeBodyFactory::privCreateCentipedeBody(sf::Vector2f pos, int row, int col, CentipedeHead* _head, CentipedeBody* _prevBody, float speed)
{
	CentipedeBody* CentipedeBodyRef;

	CentipedeBodyRef = myCentipedeBodyPool.GetCentipedeBody();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	CentipedeBodyRef->SetExternalManagement(RecycleCentipedeBody);

	//Initialize the new CentipedeBody
	CentipedeBodyRef->Initialize(pos, row, col, nullptr, _prevBody, _head, speed);

	Instance().bodyCount++;

	return CentipedeBodyRef;
}

void CentipedeBodyFactory::privRecycleCentipedeBody(GameObject* _CentipedeBodyRef)
{
	myCentipedeBodyPool.ReturnCentipedeBody(static_cast<CentipedeBody*>(_CentipedeBodyRef));
}

void CentipedeBodyFactory::Terminate()
{
	delete Instance().pDeath;

	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}

void CentipedeBodyFactory::privSendDeathCommandForScore()
{
	//Pass the score command to the manager so that it can create a command score instance
	GameManager::GetScoreMgr()->SendScoreCmd(pDeath);
}

int CentipedeBodyFactory::privGetBodyCount()
{
	return bodyCount;
}

void CentipedeBodyFactory::privResetBodyCount()
{
	bodyCount = 0;
}

void CentipedeBodyFactory::privDecrementBodyCount()
{
	ConsoleMsg::WriteLine("Body count before decrement: " + Tools::ToString(bodyCount));
	bodyCount--;
}
