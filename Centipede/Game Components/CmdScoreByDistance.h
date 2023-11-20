#ifndef _ScoreByDistance
#define _ScoreByDistance

#include "CmdScore.h"
#include <queue>

class CmdScoreByDistance : public CmdScore
{
private:
	int dNear;
	int dMed;
	int dFar;
	int vNear;
	int vMed;
	int vFar;

	//Variable to store the game object's (spider) position just before the command is sent to the score manager
	//Stored in a queue so that as position's are sent, they will be stored in the same order that they are stored in the score manager
	std::queue<sf::Vector2f> holdObjPos;

public:
	CmdScoreByDistance() = delete;
	CmdScoreByDistance(const CmdScoreByDistance&) = delete;
	CmdScoreByDistance& operator=(const CmdScoreByDistance&) = delete;
	virtual ~CmdScoreByDistance() = default;

	CmdScoreByDistance(int dNear, int dMed, int dFar,
		int vNear, int vMed, int vFar);

	virtual void Execute() override;

	void SetPos(sf::Vector2f holdPos);

	
};

#endif