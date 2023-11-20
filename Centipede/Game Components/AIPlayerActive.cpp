#include "AIPlayerActive.h"
#include "PlayerManager.h"
#include "Player.h"
#include "Grid.h"
#include "WaveManager.h"
#include "GameManager.h"
#include "AttractorMode.h"
#include "MushroomRegeneration.h"
#include "Mushroom.h"
#include "PlayMode.h"

void AIPlayerActive::HandleWaveCompleteUpdate(std::stack<Mushroom*> mushStack) const
{
	//Begin mushroom regeneration event and pass it the scene that will begin once it completes
	//MushroomRegeneration* mushroomRegenMgr = new MushroomRegeneration(mushStack, (new AttractorMode));
	GameManager::PassSceneToStart(new AttractorMode);
}

void AIPlayerActive::HandlePlayerDeath_PlayerState(std::stack<Mushroom*> mushStack) const
{
	//Begin mushroom regeneration event and pass it the scene that will begin once it completes
	//MushroomRegeneration* mushroomRegenMgr = new MushroomRegeneration(mushStack, (new AttractorMode));
	GameManager::PassSceneToStart(new AttractorMode);
}

void AIPlayerActive::HandlePlayerSwap(Player* setPlr) const
{
	//Switch back to the AI player now that the player(s) are dead
	GameManager::GetPlayerMgr()->SwapToAIPlayer();

	//Reset the player(s) now that the game has switched back to the AI mode
	GameManager::GetPlayMode()->ResetPlayers();

	//Change the scene to attractor mode now that the single player must restart
	SceneManager::ChangeScene(new AttractorMode);

	//Turn off two player mode upon switching back to the AI player
	GameManager::SetOnePlayerMode();
}
