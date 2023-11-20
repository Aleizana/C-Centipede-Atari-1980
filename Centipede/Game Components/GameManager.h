#ifndef _GameMgr
#define _GameMgr

#include "SFML/Graphics.hpp"

//Forward declarations
class WaveManager;
class SpawnerManager;
class GameObject;
class HUDManager;
class HighscoreManager;
class SoundManager;
class Scene;
class PlayMode;
class ScoreManager;
class PlayerManager;
class GridManager;

class GameManager
{
private:
	/******************************************************************
			  Currecctly set-up as a Singleton
	********************************************************************/
	static GameManager* ptrInstance;			// Game set up as a singleton

	GameManager();												// Private constructor
	GameManager(const GameManager&) = delete;				// Prevent copy-construction
	GameManager& operator=(const GameManager&) = delete;	// Prevent assignment
	~GameManager() = default;											// Only this class can delete

	static GameManager& Instance()	    // Access reference (all public methods will be static)
	{
		if (ptrInstance == nullptr)
			ptrInstance = new GameManager();
		return *ptrInstance;
	};

	//So that the game manager instance can own the wave manager and pull data from it
	WaveManager* waveMgrRef;

	//To store a reference to the spawner manager so that the wave data within the wave manager can be transferred into the enemy spawners
	SpawnerManager* spawnerMgrRef;

	//Reference to the manager that handles filling the arrays for every display and for drawing them every frame
	HUDManager* refHUD;

	//Reference to the high score manager to allow the HUD to reference it
	HighscoreManager* highscoreMgrRef;

	//Reference to the sound manager that anything that needs a sound will access
	SoundManager* soundMgrRef;

	//Reference to the score manager that will give score commands and process them every frame
	ScoreManager* scoreMgrRef;

	//Reference to the player manager that handles creating and swapping the active player object in the game
	PlayerManager* plrMgrRef;

	//Reference to the grid manager which creates grids
	GridManager* gridMgrRef;

	//To tell when a scene is done being initialized
	//Avoids issues with objects colliding during player swap
	bool sceneInitDone;

	//For processes to tell if the game is in two-player mode (true) or one-player mode (false)
	bool twoPlayerMode;
	
	//The system path for the file storing the wave data
	const char* pWaveFile = R"(..\Centipede\resources\WaveData.txt)";

	float bottomOfScreenLimit;
	float leftScreenCutoff;
	float rightScreenCutoff;

	//Multiplier for the number of cells that non-player game objects can move left or right off the screen without being destroyed
	const int offScreenRangeMultiplier = 3;

	//Stores whether the game is in two player or one player mode as a state
	PlayMode* pCurrentPlayMode;

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time. Not done for this demo however

	// Private NON_STATIC methods to perform actual work on member var
	void privSceneStartInit();

	void privGameOverSceneInit();

	//For the centipede factory to notify the game manager when there are no more centipede heads
	void privWaveComplete();

	void privPlayerDeath();

	const bool privGetSceneInitStatus() const;

	void privToggleMainSceneProcessing();

	const bool privGet2PlayerModeBool() const;

	HUDManager* privGetHUDMgr();

	HighscoreManager* privGetHighscoreMgr();

	SoundManager* privGetSoundMgr();

	void NotifyFactoriesToStoreSounds();

	void privNotifySendLoopedSounds();

	void privNotifyStopLoopedSounds();

	void privPassSceneToStart(Scene* sceneToStart);

	void privPassTwoPlayerModeSetting(bool passState);

	float privGetBottomOfScreenLimit();

	float privGetRightScreenCutoff();

	float privGetLeftScreenCutoff();

	void privSetTwoPlayerMode();
	void privSetOnePlayerMode();

	const PlayMode* privGetPlayMode() const;

	WaveManager* privGetWaveMgr() const;

	ScoreManager* privGetScoreMgr() const;

	PlayerManager* privGetPlayerMgr() const;

	GridManager* privGetGridMgr() const;

	void privSwapActivePlayer();

	//Initializes all of the game data such as managers and factories, and then switches to attractor mode
	void privGameDataSceneInit();

public:

	// Services/API as STATIC METHODS
	//    Usually just a pass-through arguments to private instance methods

	static void SceneStartInit() { Instance().privSceneStartInit(); };

	static void SceneStartInitGameOver() { Instance().privGameOverSceneInit(); };

	static void GameDataSceneInit() { Instance().privGameDataSceneInit(); };

	static void NotifyWaveComplete() { Instance().privWaveComplete(); };

	static void NotifyPlayerDeath() { Instance().privPlayerDeath(); };

	static const bool MainSceneProcessing() { return Instance().privGetSceneInitStatus(); };

	static const void ToggleMainSceneProcessingBool() { Instance().privToggleMainSceneProcessing(); };

	static HUDManager* GetHUDManager() { return Instance().privGetHUDMgr(); };

	static HighscoreManager* GetHighscoreManager() { return Instance().privGetHighscoreMgr(); };

	static const bool Get2PlayerModeBool(){ return Instance().privGet2PlayerModeBool(); };

	static SoundManager* GetSoundManager() { return Instance().privGetSoundMgr(); };

	static void Terminate();

	static void NotifyFactoriesToSendLoopedSounds_OnUnmute() { Instance().privNotifySendLoopedSounds(); };

	static void NotifyFactoriesToStopLoopedSounds_OnMute() { Instance().privNotifyStopLoopedSounds(); };

	static void PassSceneToStart(Scene* sceneToStart) { Instance().privPassSceneToStart(sceneToStart); };

	static void PassTwoPlayerModeBool(bool passState) { Instance().privPassTwoPlayerModeSetting(passState); };

	static float GetBottomOfScreenLimit() { return Instance().privGetBottomOfScreenLimit(); };
	static float GetLeftScreenCutoff() { return Instance().privGetLeftScreenCutoff(); };
	static float GetRightScreenCutoff() { return Instance().privGetRightScreenCutoff(); };

	static void SetTwoPlayerMode() { Instance().privSetTwoPlayerMode(); };
	static void SetOnePlayerMode() { Instance().privSetOnePlayerMode(); };

	static const PlayMode* GetPlayMode() { return Instance().privGetPlayMode(); };

	static WaveManager* GetWaveMgr() { return Instance().privGetWaveMgr(); };

	static ScoreManager* GetScoreMgr() { return Instance().privGetScoreMgr(); };

	static PlayerManager* GetPlayerMgr() { return Instance().privGetPlayerMgr(); };

	static GridManager* GetGridMgr() { return Instance().privGetGridMgr(); };

	static void SwapActivePlayer() { Instance().privSwapActivePlayer(); };
};

#endif
