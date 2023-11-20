#include "CmdScoreByDistance.h"
#include <iostream>
#include "ScoreManager.h"
#include "PlayerManager.h"
#include "Player.h"
#include "Blaster.h"
#include "DisplayOnDeathFactory.h"
#include "GameManager.h"

CmdScoreByDistance::CmdScoreByDistance(int dn, int dm, int df,
	int vn, int vm, int vf)
	: dNear(dn), dMed(dm), dFar(df), vNear(vn), vMed(vm), vFar(vf)
{
}

void CmdScoreByDistance::Execute()
{

	//Do not calculate score if pos queue is empty
	if (holdObjPos.empty())
	{
		return;
	}

	//Store the current position of the player
	sf::Vector2f plrPos = GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerBlaster()->GetPos();

	//Calculate the absolute value of the player's distance from the object in the x and y directions
	sf::Vector2f posDiff = plrPos - holdObjPos.front();

	posDiff.x = abs(posDiff.x);
	posDiff.y = abs(posDiff.y);

	// processing distance to score:
	if (posDiff.x <= dNear || posDiff.y <= dNear)
	{
		ConsoleMsg::WriteLine("Spider Score Distance is NEAR RANGE.");
		GameManager::GetScoreMgr()->AddScore(vNear);

		//Tell the display on death factory to show the score where the spider had died
		DisplayOnDeathFactory::CreateScoreDisplayOnSpiderDeath(holdObjPos.front(), vNear);
	}
	else if (posDiff.x <= dMed || posDiff.y <= dMed)
	{
		ConsoleMsg::WriteLine("Spider Score Distance is MEDIUM RANGE.");
		GameManager::GetScoreMgr()->AddScore(vMed);

		//Tell the display on death factory to show the score where the spider had died
		DisplayOnDeathFactory::CreateScoreDisplayOnSpiderDeath(holdObjPos.front(), vMed);
	}
	else
	{
		ConsoleMsg::WriteLine("Spider Score Distance is FAR RANGE.");
		GameManager::GetScoreMgr()->AddScore(vFar);

		//Tell the display on death factory to show the score where the spider had died
		DisplayOnDeathFactory::CreateScoreDisplayOnSpiderDeath(holdObjPos.front(), vFar);
	}

	//Remove that object's position from the queue
	holdObjPos.pop();
}

void CmdScoreByDistance::SetPos(sf::Vector2f holdPos)
{
	holdObjPos.push(holdPos);
}