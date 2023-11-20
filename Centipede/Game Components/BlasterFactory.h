// BlasterFactory
// Andre Berthiaume, April 2013

#ifndef _BlasterFactory
#define _BlasterFactory

#include "BlasterObjectPool.h"
#include "SFML/Graphics.hpp"
class GameObject;

//To store a reference to the created blaster to know when the blaster can fire
class ControllerBase;
class Blaster;
class SoundCommand;

class BlasterFactory
{
private:
	/******************************************************************
			  Currecctly set-up as a Singleton
	********************************************************************/
	static BlasterFactory* ptrInstance;			// Game set up as a singleton

	BlasterFactory();												// Private constructor
	BlasterFactory(const BlasterFactory&) = delete;				// Prevent copy-construction
	BlasterFactory& operator=(const BlasterFactory&) = delete;	// Prevent assignment
	~BlasterFactory() = default;											// Only this class can delete

	static BlasterFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (ptrInstance == nullptr)
			ptrInstance = new BlasterFactory();
		return *ptrInstance;
	};

	BlasterObjectPool myBlasterPool;  // Back to be a non-static member instance

	//Spawn point for the blaster, initialized in scene given that it involves the player
	const float blasterSpawnX = 240;
	const float blasterSpawnY = 400;
	const sf::Vector2f blasterSpawnPos = sf::Vector2f(blasterSpawnX, blasterSpawnY);

	//Blaster speed
	const float BlasterSpeedRef = 5.0f;

	//The command to pass to the sound manager to play a sound on death
	SoundCommand* pSound;

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time. Not done for this demo however

	// Private NON_STATIC methods to perform actual work on member var
	Blaster* privCreateBlaster(ControllerBase* _ctrlRef);
	void privRecycleBlaster(GameObject* _blasterRef);

	//Return the spawn pos of the blaster
	sf::Vector2f privSetBlasterSpawnPos();

	void privSendDeathSoundCommand();

	void privStoreSoundCommand();

	float privGetBlasterSpeed();

public:

	// Services/API as STATIC METHODS
	//    Usually just a pass-through arguments to private instance methods
	static Blaster* CreateBlaster(ControllerBase* _ctrlRef) { return Instance().privCreateBlaster(_ctrlRef); };
	static void RecycleBlaster(GameObject* b) { Instance().privRecycleBlaster(b); };

	//Return the spawn position of the blaster for whichever spawners need it 
	static sf::Vector2f GetBlasterSpawnPos() { return Instance().privSetBlasterSpawnPos(); };

	static void SendDeathSoundCommand() { Instance().privSendDeathSoundCommand(); };

	static void StoreSoundCommand() { Instance().privStoreSoundCommand(); };

	static void Terminate();

	static float GetBlasterSpeed() { return Instance().privGetBlasterSpeed(); };
};


#endif _BlasterFactory