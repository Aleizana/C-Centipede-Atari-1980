#ifndef _PlrMgr
#define _PlrMgr

#include <vector>

//To be able to store the active player
class Player;
class ControllerManager;
class SoundCommand;
class ActivePlayerState;

class PlayerManager
{
public:
	enum PlayerNumber { AI, Player_1, Player_2 };

private:
	//Reference to the current active player
	Player* activePlayer;

	//Vector to store each of the active players
	std::vector<Player*> plrList;

	//Reference to the controller manager which the player manager uses to set the controller for each blaster
	ControllerManager* ctrlMgrRef;

	ActivePlayerState* pActivePlayerState;

	//The y-limit through which the blaster can move
	//Also used for the centipede once it reaches the bottom of the screen
	const int playerAreaLimit = 368;
	
	PlayerNumber activePlayer_Number;

	const int plrAI_index = 0;
	const int plr1_Index = 1;
	const int plr2_Index = 2;

	//The size of the list when there are no human players, only the single AI player
	const int plrListSize_NoHumanPlayers = 1;

	//The command to pass to the sound manager to play a sound on death
	SoundCommand* pSound;

	void CreateAllPlayers();

public:
	PlayerManager();												// Private constructor
	PlayerManager(const PlayerManager&) = delete;				// Prevent copy-construction
	PlayerManager& operator=(const PlayerManager&) = delete;	// Prevent assignment
	~PlayerManager();											// Only this class can delete

	//Create a player object
	Player* CreatePlayer(int controllerEnumVal, PlayerNumber plrNum, Player* nextPlrRef = nullptr);

	void CreatePlayersInit();

	//Get the currently active player
	Player* GetActivePlayer();

	Player* GetPlayerByEnum(PlayerNumber plrNum) const;

	//Set the active player
	void StartGamePlayerSwap();

	//Creating the player to start the game
	void GameStartInit();

	//Resets the references to anything tied to GameObject upon Scene change, given that they all get deleted and recycled.
	void ResetPlayerSceneChange();

	//Tell the player manager to switch back to the AI controller
	void SwapToAIPlayer();

	void SendSoundCommand();

	void StoreSoundCommand();

	const int GetPlayerAreaLimit();

	std::vector<Player*> GetPlayerList();

	void SetActivePlayer(Player* plrToSet);

	const ActivePlayerState* GetActivePlayerState();

	const int GetPlr1Index() const;

	void SwitchToHumanPlayerState();
};

#endif
