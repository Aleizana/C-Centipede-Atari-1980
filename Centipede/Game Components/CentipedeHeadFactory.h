// CentipedeHeadFactory
// Andre Berthiaume, April 2013

#ifndef _CentipedeHeadFactory
#define _CentipedeHeadFactory

#include "CentipedeHeadObjectPool.h"
#include "SFML/Graphics.hpp"
class GameObject;

//To store a reference to the created CentipedeHead to know when the blaster can fire
class CentipedeHead;
class MoveState;
class CentipedeBody;
class CmdScore;
class SoundCommand;

class CentipedeHeadFactory
{
private:
	/******************************************************************
			  Currecctly set-up as a Singleton
	********************************************************************/
	static CentipedeHeadFactory* ptrInstance;			// Game set up as a singleton

	CentipedeHeadFactory();												// Private constructor
	CentipedeHeadFactory(const CentipedeHeadFactory&) = delete;				// Prevent copy-construction
	CentipedeHeadFactory& operator=(const CentipedeHeadFactory&) = delete;	// Prevent assignment
	~CentipedeHeadFactory() = default;											// Only this class can delete

	static CentipedeHeadFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (ptrInstance == nullptr)
			ptrInstance = new CentipedeHeadFactory();
		return *ptrInstance;
	};

	CentipedeHeadObjectPool myCentipedeHeadPool;  // Back to be a non-static member instance

	//Initial spawn for the centipede head
	const float X_SpawnMainCentipede = 256.0f;
	const float Y_SpawnTopOfScreen = 0.0f;

	//Solo heads will spawn 3 cells apart from eachother
	const int soloHeadSpawnOffset = 3;

	//The maximum number of solo heads that can spawn in the player area or the top of the screen
	const int soloHeadMaxPerSpawn = 10;

	//So that the centipede will appear above the HUD
	const int CentipedeDrawOrder = 10000;

	//To tell during any given wave when the plr area centipedes have already been spawned
	bool spawnedInPlayerArea;

	//For the wave to set when solo heads are present in the start of the wave
	bool soloHeadsPresent;

	//For the wave to set when solo heads will be present in the plr area once the centipede reaches the bottom
	bool soloHeadsPresentPlrArea;

	//Speed of the centipede head and will be referenced by the body parts as well
	float centiSpeed;

	//Speed of the solo spawning heads
	float soloHeadSpeed;

	//Speed of the solo heads in the plr area
	float soloHeadPlrAreaSpeed;

	//The number of solo heads that will spawn in the plr area once the centipede reaches the bottom
	int soloHeadSpawnInPlrAreaCount;

	//For decrementing the row of the body nodes as they are spawned
	const int BodySpawn_RowDecrement = 1;

	//To split the number of solo heads that will spawn in the player area in half so that both sides can be utilized
	const int SoloHeadPlrAreaCountDivisor = 2;

	const int leftSideOfScreen_Col = 0;

	

	const float FastSpeed = 8.0f;
	const float MediumSpeed = 4.0f;
	const float SlowSpeed = 2.0f;

	//The command to pass to the score manager to calculate the points for kill
	CmdScore* pDeath;

	int headCount;

	SoundCommand* pSound;

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time. Not done for this demo however

	// Private NON_STATIC methods to perform actual work on member var
	CentipedeHead* privCreateCentipedeHead(sf::Vector2f pos, int row, int col, const MoveState* setState, float speed, CentipedeBody* firstNode, int offsetIncr);
	void privRecycleCentipedeHead(GameObject* _CentipedeHeadRef);

	void privLevelStartSpawn(int bodySpawnNumNodes, int numSoloHeads);

	const float privGetHeadSpeed() const;

	void privSetHeadSpeed(float setSpeed);

	void privResetHeadCount();

	//For centi heads to tell the factory to send the death command for scoring upon death
	void privSendDeathCommandForScore();

	void privDecrementHeadCount();

	void privSendSoundCommand();

	void privStoreSoundCommand();

	void privStopCentiLoop();

	const int privGetCentiDrawOrder();

	void privSetSoloHeadPresent(bool status);

	void privSetSoloHeadSpeed(float speed);

	void privSetSoloHeadPresentPlrArea(bool status);

	void privSetSoloHeadPlrAreaCount(int count);

	void privSpawnPlrAreaSoloHeads();

	void privSetSoloHeadPlrAreaSpeed(float speed);

public:

	// Services/API as STATIC METHODS
	//    Usually just a pass-through arguments to private instance methods
	static CentipedeHead* CreateCentipedeHead(sf::Vector2f pos, int row, int col, const MoveState* setState, float speed, CentipedeBody* firstNode = nullptr, int offsetIncr = 0) {
		return Instance().privCreateCentipedeHead(pos, row, col, setState, speed, firstNode, offsetIncr);
	};

	static void RecycleCentipedeHead(GameObject* b) { Instance().privRecycleCentipedeHead(b); };

	static void CentipedeLevelStartSpawn(int bodySpawnNumNodes, int numSoloHeads) { Instance().privLevelStartSpawn(bodySpawnNumNodes, numSoloHeads); };

	static void Terminate();

	static const float GetHeadSpeed() { return Instance().privGetHeadSpeed(); };

	static void SetHeadSpeed(float setSpeed) { Instance().privSetHeadSpeed(setSpeed); };

	static void DecrementHeadCount() { Instance().privDecrementHeadCount(); };

	static void SendDeathCommandForScore() { Instance().privSendDeathCommandForScore(); };

	static void SendSoundCommand() { Instance().privSendSoundCommand(); };

	static void StoreSoundCommand() { Instance().privStoreSoundCommand(); };

	static void StopCentipedeLoop() { Instance().privStopCentiLoop(); };

	static const int GetCentipedeDrawOrder() { return Instance().privGetCentiDrawOrder(); };

	static void SetSoloHeadsPresent(bool status) { Instance().privSetSoloHeadPresent(status); };

	static void SetSoloHeadSpeed(float speed) { Instance().privSetSoloHeadSpeed(speed); };

	static void SetSoloHeadPlrAreaSpeed(float speed) { Instance().privSetSoloHeadPlrAreaSpeed(speed); };

	static void SetSoloHeadPresentPlrArea(bool status) { Instance().privSetSoloHeadPresentPlrArea(status); };

	static void SetSoloHeadPlrAreaCount(int count) { Instance().privSetSoloHeadPlrAreaCount(count); };

	static void SpawnPlayerAreaSoloHeads() { Instance().privSpawnPlrAreaSoloHeads(); };
};


#endif _CentipedeHeadFactory