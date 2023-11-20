#ifndef _ActivePlayerState
#define _ActivePlayerState

//#include "TEAL\CommonElements.h"
#include <stack>

class HumanPlayerActive;
class AIPlayerActive;
class Player;
class Mushroom;

class ActivePlayerState
{
public:
	ActivePlayerState() = default;
	ActivePlayerState(const ActivePlayerState&) = delete;
	ActivePlayerState& operator=(const ActivePlayerState&) = delete;
	virtual ~ActivePlayerState() = default;

	virtual void HandleWaveCompleteUpdate(std::stack<Mushroom*> mushStack) const = 0;

	virtual void HandlePlayerDeath_PlayerState(std::stack<Mushroom*> mushStack) const = 0;

	virtual void HandlePlayerSwap(Player* setPlr) const = 0;

	static const HumanPlayerActive humanPlayerState;
	static const AIPlayerActive aiPlayerState;

protected:

};

#endif