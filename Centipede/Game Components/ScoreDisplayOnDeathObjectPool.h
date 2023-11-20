// ScoreDisplayOnDeathObjectPool

#ifndef _ScoreDisplayOnDeathObjectPool
#define _ScoreDisplayOnDeathObjectPool

#include <stack>
class ScoreDisplayOnDeath;

class ScoreDisplayOnDeathObjectPool
{
private:
	std::stack<ScoreDisplayOnDeath*> recycledItems;

public:
	ScoreDisplayOnDeathObjectPool();
	ScoreDisplayOnDeathObjectPool(const ScoreDisplayOnDeathObjectPool&) = delete;
	ScoreDisplayOnDeathObjectPool& operator=(const ScoreDisplayOnDeathObjectPool&) = delete;
	~ScoreDisplayOnDeathObjectPool();

	ScoreDisplayOnDeath* GetScoreDisplayOnDeath();

	void ReturnScoreDisplayOnDeath(ScoreDisplayOnDeath* b);
};


#endif _ScoreDisplayOnDeathObjectPool
