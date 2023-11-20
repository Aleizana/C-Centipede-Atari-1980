// ScorpionFactory
// Andre Berthiaume, April 2013

#ifndef _ScorpionFactory
#define _ScorpionFactory

#include "ScorpionObjectPool.h"
#include "SFML/Graphics.hpp"
class GameObject;

//To store a reference to the created Scorpion to know when the blaster can fire
class Scorpion;
class ScorpionMover;
class ScorpionMoveBaseState;

//Variable to store the score command for scorpions
class CmdScore;
class SoundCommand;

class ScorpionFactory
{
	
public: 

private:
	/******************************************************************
			  Currecctly set-up as a Singleton
	********************************************************************/
	static ScorpionFactory* ptrInstance;			// Game set up as a singleton

	ScorpionFactory();												// Private constructor
	ScorpionFactory(const ScorpionFactory&) = delete;				// Prevent copy-construction
	ScorpionFactory& operator=(const ScorpionFactory&) = delete;	// Prevent assignment
	~ScorpionFactory() = default;											// Only this class can delete

	static ScorpionFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (ptrInstance == nullptr)
			ptrInstance = new ScorpionFactory();
		return *ptrInstance;
	};

	ScorpionObjectPool myScorpionPool;  // Back to be a non-static member instance

	ScorpionMover* scorpMoverRef;

	//ScorpionMoverObjectPool myScorpionMoverPool;  // Back to be a non-static member instance

	//The command to pass to the score manager to calculate the points for kill
	CmdScore* pDeath;

	//Value to be set by the game manager from the wave file, and to be referenced by the scorpion mover
	float scorpionSpeed;

	SoundCommand* pSound;

	//For keeping track of how many scorpions are alive so that the factory can know whether to pause the sound loop
	int scorpionCount;

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time. Not done for this demo however

	// Private NON_STATIC methods to perform actual work on member var
	void privCreateScorpion(sf::Vector2f pos, int row, int col, ScorpionMoveBaseState* setDir);
	void privRecycleScorpion(GameObject* _ScorpionRef);

	//For scorpions to tell the factory to send the death command for scoring upon death
	void privSendDeathCommandForScore();

	void privSetScorpSpeed(float scorpSpeed);

	void privSendSoundCommand();

	void privStoreSoundCommand();

	void privStopLoop();

	void privDecrementScorpCount();

public:
	// Services/API as STATIC METHODS
	//    Usually just a pass-through arguments to private instance methods
	static void CreateScorpion(sf::Vector2f pos, int row, int col, ScorpionMoveBaseState* setDir) { Instance().privCreateScorpion(pos, row, col, setDir); };
	static void RecycleScorpion(GameObject* b) { Instance().privRecycleScorpion(b); };

	static void Terminate();

	static void SendDeathCommandForScore() { Instance().privSendDeathCommandForScore(); };

	static void SetScorpionSpeed(float scorpSpeed) { Instance().privSetScorpSpeed(scorpSpeed); };

	static float GetScorpionSpeed() { return Instance().scorpionSpeed; };

	static void SendSoundCommand() { Instance().privSendSoundCommand(); };

	static void StoreSoundCommand() { Instance().privStoreSoundCommand(); };

	static void StopScorpionLoop() { Instance().privStopLoop(); };

	static void DecrementScorpionCount() { Instance().privDecrementScorpCount(); };
};


#endif _ScorpionFactory