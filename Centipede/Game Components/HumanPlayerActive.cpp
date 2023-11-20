#include "HumanPlayerActive.h"
#include "PlayerManager.h"
#include "Player.h"
#include "Grid.h"
#include "WaveManager.h"
#include "GameManager.h"
#include "MainGameScene.h"
#include "PlayMode.h"
#include "MushroomRegeneration.h"
#include "HUDManager.h"
#include "Mushroom.h"

void HumanPlayerActive::HandleWaveCompleteUpdate(std::stack<Mushroom*> mushStack) const
{
	// Increment the wave number of the player now that they have a completed a wave
	GameManager::GetPlayerMgr()->GetActivePlayer()->IncrementPlayerWaveNum();

	//If the player has reached the last wave, reset their wave number to 1
	if (GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerWaveNum() > GameManager::GetWaveMgr()->GetMaxWaves())
	{
		GameManager::GetPlayerMgr()->GetActivePlayer()->ResetWaveCount();
	}

	//Store the player's grid data
	GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->StoreGridData();
	GameManager::GetPlayerMgr()->GetActivePlayer()->SetPlayerGridStatus(true);

	//Begin mushroom regeneration event and pass it the scene that will begin once it completes
	MushroomRegeneration* mushroomRegenMgr = new MushroomRegeneration(mushStack, (new MainGameScene), false);
}

void HumanPlayerActive::HandlePlayerDeath_PlayerState(std::stack<Mushroom*> mushStack) const
{
	//Decrement the dead player's lives
	GameManager::GetPlayerMgr()->GetActivePlayer()->DecrementPlayerLives();

	//Update the display of the dead players lives
	GameManager::GetHUDManager()->ChangeLivesDisplay(GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerLives());

	GameManager::GetPlayMode()->HandlePlayerDeath(mushStack);
}

void HumanPlayerActive::HandlePlayerSwap(Player* setPlr) const
{
	//GameManager::GetPlayerMgr()->SwitchToHumanPlayerState();

	GameManager::GetPlayerMgr()->SetActivePlayer(setPlr);

	//Change the scene to attractor mode now that the single player must restart
	SceneManager::ChangeScene(new MainGameScene);
}
