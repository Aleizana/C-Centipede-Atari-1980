// MushroomFactory
// Andre Berthiaume, April 2013

#ifndef _MushroomFactory
#define _MushroomFactory

#include "MushroomObjectPool.h"
#include "SFML/Graphics.hpp"
#include <queue>

class GameObject;

//To store a reference to the created Mushroom
class Mushroom;
//To store the score commands for Mush and Poisoned Mush
class CmdScore;

class SoundCommand;

class MushroomFactory
{
private:
	/******************************************************************
			  Currecctly set-up as a Singleton
	********************************************************************/
	static MushroomFactory* ptrInstance;			// Game set up as a singleton

	MushroomFactory();												// Private constructor
	MushroomFactory(const MushroomFactory&) = delete;				// Prevent copy-construction
	MushroomFactory& operator=(const MushroomFactory&) = delete;	// Prevent assignment
	~MushroomFactory() = default;											// Only this class can delete

	static MushroomFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (ptrInstance == nullptr)
			ptrInstance = new MushroomFactory();
		return *ptrInstance;
	};

	MushroomObjectPool myMushroomPool;  // Back to be a non-static member instance

	SoundCommand* pSound;

	//Stores a count of the active mushrooms
	int mushCount = 0;

	bool initSpawn = false;

	//The max and min number of mushrooms the spawner will automatically create in each row at the beginning of the game
	static const int maxMushSpawnRow = 2;
	static const int minMushSpawnRow = 0;

	static const int mushroomFirstRowToSpawn = 2;

	//References to the death score commands for mushrooms
	CmdScore* pMushDeath;
	CmdScore* pPoisonMushDeath;
	CmdScore* pMushRegen;

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time. Not done for this demo however

	// Private NON_STATIC methods to perform actual work on member var
	bool privCreateMushroom(int row, int col);
	void privRecycleMushroom(GameObject* _MushroomRef);

	//Creates the mushroom field at the start of the game
	void privInitMushroomField();

	//For mushrooms to tell the factory to send the death command for scoring upon death
	void privSendDeathCommandForScore_NoPoison();
	void privSendDeathCommandForScore_Poison();

	//For the mushroom regeneration process to begin through the mushroom factory
	void privSendMushroomRegenScoreCommand();

	void privSendSoundCommand();

	void privStoreSoundCommand();

public:

	// Services/API as STATIC METHODS
	//    Usually just a pass-through arguments to private instance methods
	static bool CreateMushroom(int row, int col) { return Instance().privCreateMushroom(row, col); };
	static void RecycleMushroom(GameObject* b) { Instance().privRecycleMushroom(b); };

	static void InitMushroomField() { Instance().privInitMushroomField(); };

	static void Terminate();

	static void SendDeathCommandForScore_NoPoison() { Instance().privSendDeathCommandForScore_NoPoison(); };

	static void SendDeathCommandForScore_Poison() { Instance().privSendDeathCommandForScore_Poison(); };

	static int GetMushCount() { return Instance().mushCount; };

	static void SendMushRegenScoreCommand() { Instance().privSendMushroomRegenScoreCommand(); };

	static void SendSoundCommand() { Instance().privSendSoundCommand(); };

	static void StoreSoundCommand() { Instance().privStoreSoundCommand(); };
};


#endif _MushroomFactory