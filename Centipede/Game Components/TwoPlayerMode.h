#ifndef _TwoPlayerMode
#define _TwoPlayerMode

#include "TEAL\CommonElements.h"
#include "PlayMode.h"

class TwoPlayerMode;
class PlayerManager;

class TwoPlayerMode : public PlayMode
{
public:
	TwoPlayerMode() = default;
	TwoPlayerMode(const TwoPlayerMode&) = delete;
	TwoPlayerMode& operator=(const TwoPlayerMode&) = delete;
	virtual ~TwoPlayerMode() = default;

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
	const int maxPlayers = 3;

};

#endif