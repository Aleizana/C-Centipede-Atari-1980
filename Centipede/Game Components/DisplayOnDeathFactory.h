// DisplayOnDeathFactory
// Andre Berthiaume, April 2013

#ifndef _DisplayOnDeathFactory
#define _DisplayOnDeathFactory

#include "ExplosionObjectPool.h"
#include "ScoreDisplayOnDeathObjectPool.h"
#include "SFML/Graphics.hpp"
class GameObject;

class SoundCommand;

class DisplayOnDeathFactory
{
private:
	/******************************************************************
			  Currecctly set-up as a Singleton
	********************************************************************/
	static DisplayOnDeathFactory* ptrInstance;			// Game set up as a singleton

	DisplayOnDeathFactory();												// Private constructor
	DisplayOnDeathFactory(const DisplayOnDeathFactory&) = delete;				// Prevent copy-construction
	DisplayOnDeathFactory& operator=(const DisplayOnDeathFactory&) = delete;	// Prevent assignment
	~DisplayOnDeathFactory() = default;											// Only this class can delete

	static DisplayOnDeathFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (ptrInstance == nullptr)
			ptrInstance = new DisplayOnDeathFactory();
		return *ptrInstance;
	};

	ExplosionObjectPool myExplosionPool;  // Back to be a non-static member instance
	ScoreDisplayOnDeathObjectPool myScoreDisplayPool; // Back to be a non-static member instance

	SoundCommand* pDeathSound;

	//Tells the explosion to divide the width of the explosion by 2 so that it can be 1by1
	float scalar1By1 = 2.0f;

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time. Not done for this demo however

	// Private NON_STATIC methods to perform actual work on member var
	void privCreateExplosion1By1(sf::Vector2f pos, bool plrDeath);
	void privCreateExplosion2By1(sf::Vector2f pos, bool plrDeath);
	void privCreateScoreDisplayOnSpiderDeath(sf::Vector2f pos, int score);
	void privRecycleExplosion(GameObject* _ExplosionRef);
	void privRecycleScoreDisplay(GameObject* _ScoreDisplayRef);
	void privStoreSoundCommand();
	void privSendSoundCommand();

public:

	// Services/API as STATIC METHODS
	//    Usually just a pass-through arguments to private instance methods
	static void CreateExplosion1By1(sf::Vector2f pos) { Instance().privCreateExplosion1By1(pos, false); };
	static void CreateExplosion2By1(sf::Vector2f pos) { Instance().privCreateExplosion2By1(pos, false); };
	static void CreateExplosionPlayerDeath(sf::Vector2f pos) { Instance().privCreateExplosion2By1(pos, true); };
	static void CreateScoreDisplayOnSpiderDeath(sf::Vector2f pos, int score) { Instance().privCreateScoreDisplayOnSpiderDeath(pos, score); };
	static void RecycleExplosion(GameObject* b) { Instance().privRecycleExplosion(b); };
	static void RecycleScoreDisplay(GameObject* b) { Instance().privRecycleScoreDisplay(b); };
	static void SendSoundCommand() { Instance().privSendSoundCommand(); };
	static void StoreSoundCommand() { Instance().privStoreSoundCommand(); };

	static void Terminate();
};


#endif _DisplayOnDeathFactory