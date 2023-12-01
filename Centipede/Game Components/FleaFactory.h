// FleaFactory
// Andre Berthiaume, April 2013

#ifndef _FleaFactory
#define _FleaFactory

#include "FleaObjectPool.h"
#include "SFML/Graphics.hpp"
class GameObject;

//To store a reference to the created Flea to know when the blaster can fire
class Flea;
class FleaMover;
class SoundCommand;

//Variable to store the score command for fleas
class CmdScore;

class FleaFactory
{
private:
	/******************************************************************
			  Currecctly set-up as a Singleton
	********************************************************************/
	static FleaFactory* ptrInstance;			// Game set up as a singleton

	FleaFactory();												// Private constructor
	FleaFactory(const FleaFactory&) = delete;				// Prevent copy-construction
	FleaFactory& operator=(const FleaFactory&) = delete;	// Prevent assignment
	~FleaFactory() = default;											// Only this class can delete

	static FleaFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (ptrInstance == nullptr)
			ptrInstance = new FleaFactory();
		return *ptrInstance;
	};

	FleaObjectPool myFleaPool;  // Back to be a non-static member instance

	//The command to pass to the score manager to calculate the points for kill
	CmdScore* pDeath;

	SoundCommand* pSound;

	FleaMover* fleaMoverRef;

	const int defaultIfChanceToTriggerIsZero = 1;

	int chanceToTriggerMushSpawn;

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time. Not done for this demo however

	// Private NON_STATIC methods to perform actual work on member var
	void privCreateFlea(sf::Vector2f pos, int row, int col);
	void privRecycleFlea(GameObject* _FleaRef);

	//For fleas to tell the factory to send the death command for scoring upon death
	void privSendDeathCommandForScore();

	void privSendSoundCommand();

	void privStoreSoundCommand();

	void privSetChanceToTriggerMushSpawn(int setNum);

	int privGetChanceToTriggerMushSpawn();

public:

	// Services/API as STATIC METHODS
	//    Usually just a pass-through arguments to private instance methods
	static void CreateFlea(sf::Vector2f pos, int row, int col) { Instance().privCreateFlea(pos, row, col); };
	static void RecycleFlea(GameObject* b) { Instance().privRecycleFlea(b); };

	static void Terminate();

	static void SendDeathCommandForScore() { Instance().privSendDeathCommandForScore(); };

	static void SendSoundCommand() { Instance().privSendSoundCommand(); };

	static void StoreSoundCommand() { Instance().privStoreSoundCommand(); };

	static void SetFleaChanceToTriggerMushSpawn(int setNum) { Instance().privSetChanceToTriggerMushSpawn(setNum); };

	static int GetFleaChanceToTriggerMushSpawn() { return Instance().privGetChanceToTriggerMushSpawn(); };
};


#endif _FleaFactory