#ifndef _ScoreManager
#define _ScoreManager

#include <queue>

class CmdScore;

class ScoreManager
{
private:
	// Score values;
	const int CentipedeBodyDeath = 10;
	const int CentipedeHeadDeath = 100;

	const int FleaDeath = 200;

	const int ScorpionDeath = 1000;

	const int MushroomDeath = 1;
	const int MushroomPoisonDeath = 5;
	const int MushroomRegen = 5;

	const int SpiderDeathFar = 300;
	const int SpiderDistFar = 64;

	const int SpiderDeathMedium = 600;
	const int SpiderDistMedium = 32;

	const int SpiderDeathNear = 900;
	const int SpiderDistNear = 16;

	const int ExtraLifeScore = 12000;

	ScoreManager(const ScoreManager&) = delete;
	ScoreManager& operator=(const ScoreManager&) = delete;

	std::queue<CmdScore*> QueueCmds;

public:
	// events
	enum ScoreEvents { FleaKilled, ScorpionKilled, MushroomKilled, MushroomPoisonKilled, SpiderKilled, CentipedeHeadKilled, CentipedeBodyKilled, MushroomRegeneration };

	void AddScore(int val);

	CmdScore* GetScoreCommand(ScoreEvents ev);

	void SendScoreCmd(CmdScore* c);

	ScoreManager() = default;
	~ScoreManager() = default;

	void ProcessScores();

	int GetScoreForExtraLife();

	int GetFarSpiderScore();

	int GetMedSpiderScore();

	int GetCloseSpiderScore();
};

#endif