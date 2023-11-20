#ifndef _PlayerData
#define _PlayerData

class GameGrid;
class Blaster;
class Scene;
class ControllerBase;
class ActivePlayerState;

class Player
{
private:
	//Stores the number of lives the current player has
	int lives;

	//Stores the score of the current player
	int score;

	//Stores the wave number of the current player
	int waveNum;

	//Stores a reference to the grid of the current player
	GameGrid* gridRef;

	//Tells whether the player has had a mushroom field initialized for it's grid
	bool storedGrid;

	//Stores a reference to the player's blaster
	Blaster* myBlaster;

	//Stores the integer corressponding to the enumeration value of the player number that this player is (i.e. AI = 0, Player_1 = 1, Player_2 = 2)
	int myPlayerNum;

	//Stores a reference to the controller that this player uses
	ControllerBase* ctrlRef;

	//Stores the integer corressponding to the enumeration value of the controller type that this player has (i.e. KEYBOARD = 0, AI = 1)
	int controllerEnumVal;

	//For keeping track of the number of times the player has earned an extra life so that it can act as a multiplier for the score value needed to receive another
	int extraLifeCounter;

	//The number of lives each player will start with
	static const int startingLives = 3;

	//Pointer to the player that will be switched to when this player dies
	Player* pNextPlayer;

	//Store the player state that represents the kind of player this is
	ActivePlayerState* pActivePlayerState;

public:
	Player();
	Player& operator=(const Player&) = delete;
	Player(Player& _copyBlaster) = delete;
	~Player() = default;

	//To reset the player after a game over
	void ResetPlayer();

	void AddScoreToPlayer(int val);
	const int GetPlayerScore() const;

	void SetPlayerBlaster(Blaster* blstrRef);
	Blaster* GetPlayerBlaster();

	void SetPlayerGrid(GameGrid* setGrid);
	GameGrid* GetPlayerGrid();

	bool GetPlayerGridStatus();
	void SetPlayerGridStatus(bool activeGridData);

	int GetPlayerWaveNum();
	void IncrementPlayerWaveNum();
	void ResetWaveCount();

	void DecrementPlayerLives();
	const int GetPlayerLives() const;

	int GetPlayerNumber();
	void SetPlayerNum(int setNum);

	void SetPlayerController(ControllerBase* setCtrlRef);
	ControllerBase* GetPlayerController() const;

	void SetControllerEnum(int setNum);
	int GetControllerEnum();

	void SetNextPlayer(Player* nextPlrRef);
	//void SetPrevPlayer(Player* prevPlrRef);

	Player* GetNextPlayer();
	//Player* GetPrevPlayer();

	void SwapFocusToThisPlayer();

	void SetPlayerState(const ActivePlayerState* plrState);
	const ActivePlayerState* GetMyActivePlayerState();


};

#endif
