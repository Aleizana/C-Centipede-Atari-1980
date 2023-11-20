#include "GameManager.h"
#include "WaveManager.h"
#include "SpawnerManager.h"
#include "PlayerManager.h"
#include "Player.h"
#include "Wave.h"
#include "SpiderSpawner.h"
#include "FleaSpawner.h"
#include "ScorpionSpawner.h"
#include "CentipedeHeadFactory.h"
#include "CentipedeBodyFactory.h"
#include "../Game Components/TEAL/WindowManager.h"
#include "TEAL\CommonElements.h"
#include "MainGameScene.h"
#include "Grid.h"
#include "HUDManager.h"
#include "HighscoreManager.h"
#include "AttractorMode.h"
#include "HUDMainGame.h"
#include "HUDAttractor.h"
#include "HUDGameOver.h"
#include "ScoreInputManager.h"
#include "GameOverScene.h"
#include "SoundManager.h"
#include "BlasterFactory.h"
#include "FleaFactory.h"
#include "MushroomFactory.h"
#include "DartFactory.h"
#include "SpiderFactory.h"
#include "MushroomRegeneration.h"
#include <stack>
#include "DisplayOnDeathFactory.h"
#include "PlayMode.h"
#include "ActivePlayerState.h"
#include "ScoreManager.h"

GameManager* GameManager::ptrInstance = nullptr;

GameManager::GameManager()
	: waveMgrRef(nullptr), spawnerMgrRef(nullptr), refHUD(nullptr), highscoreMgrRef(nullptr), soundMgrRef(nullptr), scoreMgrRef(nullptr), plrMgrRef(nullptr), gridMgrRef(nullptr),
		sceneInitDone(false), twoPlayerMode(false), bottomOfScreenLimit(0.0f), leftScreenCutoff(0.0f), rightScreenCutoff(0.0f), pCurrentPlayMode(nullptr)
{
	//Black window
	WindowManager::SetBackgroundColor(sf::Color(0, 0, 0, 255));
}

void GameManager::privSceneStartInit()
{
	sceneInitDone = false;

	plrMgrRef->ResetPlayerSceneChange();

	//Need to create a new HUD manager at the start of every scene
	//Create a different HUD based on if the game is in attractor mode or if the game is in main-processing
	if (plrMgrRef->GetActivePlayer()->GetPlayerNumber() == (int)plrMgrRef->PlayerNumber::AI)
	{
		refHUD = new HUDAttractor;
	}
	else
	{
		refHUD = new HUDMainGame;
	}


	Wave* holdWave = waveMgrRef->GetWaveByNumber(plrMgrRef->GetActivePlayer()->GetPlayerWaveNum());


	//Tell the spawner to reinitialize all of it's enemy spawners
	spawnerMgrRef->InitSpawners();

	//Pass wave data onto each of the spawners
	spawnerMgrRef->GetSpiderSpawner()->SetSpiderSpawnParams(holdWave->GetSpiderPresentWave(), holdWave->GetSpiderSpawnRateWave(), holdWave->GetSpiderSpeedWave());
	spawnerMgrRef->GetFleaSpawner()->SetFleaSpawnParams(holdWave->GetFleaPresentWave(), holdWave->GetFleaNumMushToTriggerWave(), holdWave->GetFleaChanceToTriggerMushSpawn());
	spawnerMgrRef->GetScorpSpawner()->SetScorpSpawnParams(holdWave->GetScorpionPresentWave(), holdWave->GetScorpionSpawnRateWave(), holdWave->GetScorpionSpeedWave());

	//Set the speed of the main centipede body
	CentipedeHeadFactory::SetHeadSpeed(holdWave->GetCentiSpeedWave());
	//Set the speed of the solo heads
	CentipedeHeadFactory::SetSoloHeadSpeed(holdWave->GetSoloHeadSpeed());
	//Set whether solo heads will be present at the start of the game
	CentipedeHeadFactory::SetSoloHeadsPresent(holdWave->GetSingleHeadPresent());
	//Set whether the solo heads will be present in the plr area once the centipede has reached the bottom of the screen
	CentipedeHeadFactory::SetSoloHeadPresentPlrArea(holdWave->GetSingleHeadPresentInPlrArea());
	//Set the number of solo heads that will be present in the plr area
	CentipedeHeadFactory::SetSoloHeadPlrAreaCount(holdWave->GetSingleHeadSpawnInPlrAreaCount());
	//Set the speed of the solo heads in the plr area
	CentipedeHeadFactory::SetSoloHeadPlrAreaSpeed(holdWave->GetSoloHeadPlrAreaSpeed());

	//Spawn the centipede at the start of the level
	CentipedeHeadFactory::CentipedeLevelStartSpawn(holdWave->GetCentiLenWave(), holdWave->GetCentiSingleHeadSpawnWave());

	sceneInitDone = true;
}

void GameManager::privGameOverSceneInit()
{
	sceneInitDone = false;

	refHUD = new HUDGameOver();

	//Initiate the highscore initial input
	if (highscoreMgrRef->CheckForNewHighScore(plrMgrRef->GetActivePlayer()->GetPlayerScore()))
	{
		//Initiate the input for the player's initials for their high score
		//Pass the font used by the HUD, the highscore manager so that it may pass the initials once entered, and the position that the initials will be displayed as the player types
		ScoreInputManager* tempInputMgr = new ScoreInputManager(refHUD->GetFont(), static_cast<HUDGameOver*>(refHUD)->GetBottomOfDisplayPos());
	}
	else
	{
		//Sleep for 3 seconds before going to the next screen
		Sleep(3000);

		pCurrentPlayMode->HandleGameOver();
	}
}

void GameManager::Terminate()
{
	delete ptrInstance->waveMgrRef;
	delete ptrInstance->spawnerMgrRef;
	delete ptrInstance->highscoreMgrRef;
	delete ptrInstance->soundMgrRef;
	delete ptrInstance->scoreMgrRef;
	delete ptrInstance->plrMgrRef;
	delete ptrInstance->gridMgrRef;

	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}

void GameManager::privWaveComplete()
{
	sceneInitDone = false;

	//Stop all looped sounds on player death
	privNotifyStopLoopedSounds();

	//Activate the mushroom regeneration of the player's grid
	std::stack<Mushroom*> holdMushStack = plrMgrRef->GetActivePlayer()->GetPlayerGrid()->GenerateMushroomRegenStack_Score();

	plrMgrRef->GetActivePlayerState()->HandleWaveCompleteUpdate(holdMushStack);
	
}

void GameManager::privPlayerDeath()
{
	//Process to initialize a new scene has begun
	sceneInitDone = false;

	//Stop all looped sounds on player death
	privNotifyStopLoopedSounds();

	//Activate the mushroom regeneration of the player's grid
	std::stack<Mushroom*> holdMushStack = plrMgrRef->GetActivePlayer()->GetPlayerGrid()->GenerateMushroomRegenStack_Score();

	plrMgrRef->GetActivePlayerState()->HandlePlayerDeath_PlayerState(holdMushStack);
}

const bool GameManager::privGetSceneInitStatus() const
{
	return sceneInitDone;
}

void GameManager::privToggleMainSceneProcessing()
{
	sceneInitDone = !sceneInitDone;
}

const bool GameManager::privGet2PlayerModeBool() const
{
	return twoPlayerMode;
}

HUDManager* GameManager::privGetHUDMgr()
{
	return refHUD;
}

HighscoreManager* GameManager::privGetHighscoreMgr()
{
	return highscoreMgrRef;
}

SoundManager* GameManager::privGetSoundMgr()
{
	return soundMgrRef;
}

void GameManager::NotifyFactoriesToStoreSounds()
{
	DisplayOnDeathFactory::StoreSoundCommand();
	CentipedeHeadFactory::StoreSoundCommand();
	BlasterFactory::StoreSoundCommand();
	FleaFactory::StoreSoundCommand();
	ScorpionFactory::StoreSoundCommand();
	MushroomFactory::StoreSoundCommand();
	DartFactory::StoreSoundCommand();
	SpiderFactory::StoreSoundCommand();
	plrMgrRef->StoreSoundCommand();
}

void GameManager::privNotifySendLoopedSounds()
{
	CentipedeHeadFactory::SendSoundCommand();
	ScorpionFactory::SendSoundCommand();
	SpiderFactory::SendSoundCommand();
}

void GameManager::privNotifyStopLoopedSounds()
{
	CentipedeHeadFactory::StopCentipedeLoop();;
	ScorpionFactory::StopScorpionLoop();
	SpiderFactory::StopSpiderLoop();
}

void GameManager::privPassSceneToStart(Scene* sceneToStart)
{
	SceneManager::ChangeScene(sceneToStart);
}

void GameManager::privPassTwoPlayerModeSetting(bool passState)
{
	twoPlayerMode = passState;
}

float GameManager::privGetBottomOfScreenLimit()
{
	return bottomOfScreenLimit;
}

float GameManager::privGetLeftScreenCutoff()
{
	return leftScreenCutoff;
}

void GameManager::privSetTwoPlayerMode()
{
	pCurrentPlayMode = (PlayMode*)&PlayMode::twoPlayerState;
	twoPlayerMode = true;
}

void GameManager::privSetOnePlayerMode()
{
	pCurrentPlayMode = (PlayMode*)&PlayMode::onePlayerState;
	twoPlayerMode = false;
}

const PlayMode* GameManager::privGetPlayMode() const
{
	return pCurrentPlayMode;
}

WaveManager* GameManager::privGetWaveMgr() const
{
	return waveMgrRef;
}

ScoreManager* GameManager::privGetScoreMgr() const
{
	return scoreMgrRef;
}

PlayerManager* GameManager::privGetPlayerMgr() const
{
	return plrMgrRef;
}

GridManager* GameManager::privGetGridMgr() const
{
	return gridMgrRef;
}

void GameManager::privSwapActivePlayer()
{
	pCurrentPlayMode->SwapActivePlayer(plrMgrRef);
}

void GameManager::privGameDataSceneInit()
{
	gridMgrRef = new GridManager;

	plrMgrRef = new PlayerManager;

	//Start the game in one player mode
	pCurrentPlayMode = (PlayMode*)&PlayMode::onePlayerState;

	//Create a new instance of high score manager
	highscoreMgrRef = new HighscoreManager;

	//Create the wave manager and have it load the wave data from the wave file
	waveMgrRef = new WaveManager(pWaveFile);

	//Initialize each of the spawners for the game objects
	spawnerMgrRef = new SpawnerManager();

	//Initialize the sound manager
	soundMgrRef = new SoundManager();

	//Initialize the score manager
	scoreMgrRef = new ScoreManager;

	//Tell the player manager to create a player at the start of the game
	plrMgrRef->GameStartInit();

	NotifyFactoriesToStoreSounds();

	bottomOfScreenLimit = (float)(WindowManager::Window().getSize().y - (gridMgrRef->GetPixelDistance() / gridMgrRef->GetPixelDistanceOffset()));
	leftScreenCutoff = 0.0f - ((float)gridMgrRef->GetPixelDistance() * offScreenRangeMultiplier);

	rightScreenCutoff = ((float)WindowManager::Window().getSize().x + ((float)gridMgrRef->GetPixelDistance() * offScreenRangeMultiplier));

	//Switch to the attractor mode to start the game
	SceneManager::ChangeScene(new AttractorMode);
}

float GameManager::privGetRightScreenCutoff()
{
	return rightScreenCutoff;
}
