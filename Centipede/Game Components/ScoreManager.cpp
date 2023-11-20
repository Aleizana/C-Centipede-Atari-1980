#include "ScoreManager.h"
#include "PlayerManager.h"
#include "Player.h"

#include <iostream>
#include "CmdScoreByValue.h"
#include "CmdScoreByDistance.h"
#include "TEAL\CommonElements.h"
#include "GameManager.h"

CmdScore* ScoreManager::GetScoreCommand(ScoreEvents ev)
{

	CmdScore* pCmd = nullptr;
	ConsoleMsg::WriteLine("Score Manager: Constructing score command for ");

	switch (ev)
	{
	case ScoreEvents::FleaKilled:
		ConsoleMsg::WriteLine("\tFleaDeath");
		pCmd = new CmdScoreValue(FleaDeath);
		break;
	case ScoreEvents::ScorpionKilled:
		ConsoleMsg::WriteLine("\tScorpionDeath");
		pCmd = new CmdScoreValue(ScorpionDeath);
		break;
	case ScoreEvents::MushroomKilled:
		ConsoleMsg::WriteLine("\tMushroomDeath");
		pCmd = new CmdScoreValue(MushroomDeath);
		break;
	case ScoreEvents::SpiderKilled:
		ConsoleMsg::WriteLine("\tSpiderDeath");
		pCmd = new CmdScoreByDistance(SpiderDistNear, SpiderDistMedium, SpiderDistFar,
			SpiderDeathNear, SpiderDeathMedium, SpiderDeathFar);
		break;
	case ScoreEvents::MushroomPoisonKilled:
		ConsoleMsg::WriteLine("\tMushroomPoisonedDeath");
		pCmd = new CmdScoreValue(MushroomPoisonDeath);
		break;
	case ScoreEvents::CentipedeHeadKilled:
		ConsoleMsg::WriteLine("\tCentipedeHeadDeath");
		pCmd = new CmdScoreValue(CentipedeHeadDeath);
		break;
	case ScoreEvents::CentipedeBodyKilled:
		ConsoleMsg::WriteLine("\tCentipedeBodyDeath");
		pCmd = new CmdScoreValue(CentipedeBodyDeath);
		break;
	case ScoreEvents::MushroomRegeneration:
		ConsoleMsg::WriteLine("\tMushroomRegen");
		pCmd = new CmdScoreValue(MushroomRegeneration);
		break;
	default:
		ConsoleMsg::WriteLine("\t<nothing>");
		break;
	}

	return pCmd;
}

void ScoreManager::AddScore(int val)
{
	ConsoleMsg::WriteLine("\tCurrent player score -> Add " + Tools::ToString(val) + " points.");

	//Tell the player manager to increase the score of the active player
	GameManager::GetPlayerMgr()->GetActivePlayer()->AddScoreToPlayer(val);
	
	// Note: Depending on implementations, this *may* need to be a strategy pattern:
	//      - regular mode: add score to current player
	//      - Critter-recall mode (level change): do nothing
}

void ScoreManager::SendScoreCmd(CmdScore* c)
{
	QueueCmds.push(c);
}

void ScoreManager::ProcessScores()
{
	if (!QueueCmds.empty())
	{
		ConsoleMsg::WriteLine("Processing all scores commands for this frame:");
	}
	
	CmdScore* c;

	while (!QueueCmds.empty())
	{
		c = QueueCmds.front();
		c->Execute();

		QueueCmds.pop();
	}
}

int ScoreManager::GetScoreForExtraLife()
{
	return ExtraLifeScore;
}

int ScoreManager::GetFarSpiderScore()
{
	return SpiderDeathFar;
}

int ScoreManager::GetMedSpiderScore()
{
	return SpiderDeathMedium;
}

int ScoreManager::GetCloseSpiderScore()
{
	return SpiderDeathNear;
}


