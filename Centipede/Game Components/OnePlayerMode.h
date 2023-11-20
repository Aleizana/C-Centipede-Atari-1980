#ifndef _OnePlayerMode
#define _OnePlayerMode

#include "TEAL\CommonElements.h"
#include "PlayMode.h"
#include <stack>

class PlayerManager;
class Mushroom;

class OnePlayerMode : public PlayMode
{
public:
	OnePlayerMode() = default;
	OnePlayerMode(const OnePlayerMode&) = delete;
	OnePlayerMode& operator=(const OnePlayerMode&) = delete;
	virtual ~OnePlayerMode() = default;

	//Set the active player
	virtual void SwapActivePlayer(PlayerManager* mgrRef) const;

	//Create a player object
	virtual void CreatePlayers(PlayerManager* mgrRef) const;

	virtual const int GetMaxPlayers() const;

	virtual void HandleGameOver() const;

	virtual void HandlePlayerDeath(std::stack<Mushroom*> mushStack) const;

	virtual void ResetPlayers() const;

private:

	//AI + Single Human Player
	const int maxPlayers = 2;

};

#endif