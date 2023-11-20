#ifndef _PlayMode
#define _PlayMode

#include "TEAL\CommonElements.h"
#include <stack>

class OnePlayerMode;
class TwoPlayerMode;
class PlayerManager;
class Mushroom;

class PlayMode
{
public:
	PlayMode() = default;
	PlayMode(const PlayMode&) = delete;
	PlayMode& operator=(const PlayMode&) = delete;
	virtual ~PlayMode() = default;

	//Set the active player
	virtual void SwapActivePlayer(PlayerManager* mgrRef) const = 0;

	//Create a player object
	virtual void CreatePlayers(PlayerManager* mgrRef) const = 0;

	virtual const int GetMaxPlayers() const = 0;

	virtual void HandleGameOver() const = 0;

	virtual void HandlePlayerDeath(std::stack<Mushroom*> mushStack) const = 0;

	virtual void ResetPlayers() const = 0;

	static const OnePlayerMode onePlayerState;
	static const TwoPlayerMode twoPlayerState;

protected:


};

#endif