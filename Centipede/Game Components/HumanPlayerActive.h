#ifndef _HumanPlayerActive
#define _HumanPlayerActive

//#include "TEAL\CommonElements.h"
#include "ActivePlayerState.h"
#include <stack>

class Mushroom;

class HumanPlayerActive : public ActivePlayerState
{
public:
	HumanPlayerActive() = default;
	HumanPlayerActive(const HumanPlayerActive&) = delete;
	HumanPlayerActive& operator=(const HumanPlayerActive&) = delete;
	virtual ~HumanPlayerActive() = default;

	virtual void HandleWaveCompleteUpdate(std::stack<Mushroom*> mushStack) const;

	virtual void HandlePlayerDeath_PlayerState(std::stack<Mushroom*> mushStack) const;

	virtual void HandlePlayerSwap(Player* setPltr) const;

private:


};

#endif