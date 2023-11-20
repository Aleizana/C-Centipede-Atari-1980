#ifndef _AIPlayerActive
#define _AIPlayerActive

//#include "TEAL\CommonElements.h"
#include "ActivePlayerState.h"
#include <stack>

class Mushroom;
class Player;

class AIPlayerActive : public ActivePlayerState
{
public:
	AIPlayerActive() = default;
	AIPlayerActive(const AIPlayerActive&) = delete;
	AIPlayerActive& operator=(const AIPlayerActive&) = delete;
	virtual ~AIPlayerActive() = default;

	virtual void HandleWaveCompleteUpdate(std::stack<Mushroom*> mushStack) const;

	virtual void HandlePlayerDeath_PlayerState(std::stack<Mushroom*> mushStack) const;

	virtual void HandlePlayerSwap(Player* setPlr) const;

protected:


};

#endif