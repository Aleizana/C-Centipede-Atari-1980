// SpiderFactory
// Andre Berthiaume, April 2013

#ifndef _SpiderFactory
#define _SpiderFactory

#include "SpiderObjectPool.h"
#include "SFML/Graphics.hpp"
class GameObject;

//To store a reference to the created Spider to know when the blaster can fire
class Spider;
class SpiderMover;
class SpiderMoveState;

//Variable to store the score command for scorpions
class CmdScore;
class SoundCommand;

class SpiderFactory
{
public:
	const enum SpiderMainDirection {LEFT, RIGHT};

private:
	/******************************************************************
			  Currecctly set-up as a Singleton
	********************************************************************/
	static SpiderFactory* ptrInstance;			// Game set up as a singleton

	SpiderFactory();												// Private constructor
	SpiderFactory(const SpiderFactory&) = delete;				// Prevent copy-construction
	SpiderFactory& operator=(const SpiderFactory&) = delete;	// Prevent assignment
	~SpiderFactory() = default;											// Only this class can delete

	static SpiderFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (ptrInstance == nullptr)
			ptrInstance = new SpiderFactory();
		return *ptrInstance;
	};

	SpiderObjectPool mySpiderPool;  // Back to be a non-static member instance

	//SpiderMoverObjectPool mySpiderMoverPool;  // Back to be a non-static member instance

	SpiderMover* spiderMoverRef;

	//Spider game properties
	float SpiderSpeed;

	//The command to pass to the score manager to calculate the points for kill
	CmdScore* pDeath;

	//For keeping track of how many spiders are alive so that the factory can know whether to pause the sound loop
	int spiderCount;

	SoundCommand* pSound;

	static const int SpiderArraySize = 6;

	const SpiderMoveState* SpiderStateArray[SpiderArraySize];

	//For the spider to reference when choosing left or right upon spawn
	const int LeftStateArrayVal = 0;
	const int RightStateArrayVal = 4;

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time. Not done for this demo however

	// Private NON_STATIC methods to perform actual work on member var
	void privCreateSpider(sf::Vector2f pos, int row, int col, SpiderMainDirection setDir);
	void privRecycleSpider(GameObject* _SpiderRef);

	//Returns the speed of the spider
	float privGetSpiderSpeed();

	void privSetSpiderSpeed(float spdrSpeed);

	//For spiders to tell the factory to send the death command for scoring upon death
	void privSendDeathCommandForScore(sf::Vector2f spiderPos);

	void privSendSoundCommand();

	void privStoreSoundCommand();

	void privStopSpiderLoop();

	const SpiderMoveState* privGetSpiderState(int index);

	const SpiderMoveState* privGetLeftDirState();

	const SpiderMoveState* privGetRightDirState();

public:

	// Services/API as STATIC METHODS
	//    Usually just a pass-through arguments to private instance methods
	static void CreateSpider(sf::Vector2f pos, int row, int col, SpiderMainDirection setDir) { Instance().privCreateSpider(pos, row, col, setDir); };
	static void RecycleSpider(GameObject* b) { Instance().privRecycleSpider(b); };

	static float GetSpiderSpeed() { return Instance().privGetSpiderSpeed(); };

	static void SetSpiderSpeed(float spdrSpeed) { Instance().privSetSpiderSpeed(spdrSpeed); };

	static void SendDeathCommandForScore(sf::Vector2f spiderPos) { Instance().privSendDeathCommandForScore(spiderPos); };

	static void Terminate();

	static void SendSoundCommand() { Instance().privSendSoundCommand(); };

	static void StoreSoundCommand() { Instance().privStoreSoundCommand(); };

	static void StopSpiderLoop() { Instance().privStopSpiderLoop(); };

	static const SpiderMoveState* GetSpiderStateByIndex(int index) { return Instance().privGetSpiderState(index); };

	static const SpiderMoveState* GetLeftDirState() { return Instance().privGetLeftDirState(); };

	static const SpiderMoveState* GetRightDirState() { return Instance().privGetRightDirState(); };
};


#endif _SpiderFactory