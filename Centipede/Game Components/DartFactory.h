// DartFactory
// Andre Berthiaume, April 2013

#ifndef _DartFactory
#define _DartFactory

#include "DartObjectPool.h"
#include "SFML/Graphics.hpp"
class GameObject;

//To store a reference to the created dart to know when the blaster can fire
class Dart;
class SoundCommand;

class DartFactory
{
private:
	/******************************************************************
			  Currecctly set-up as a Singleton
	********************************************************************/
	static DartFactory* ptrInstance;			// Game set up as a singleton

	DartFactory();												// Private constructor
	DartFactory(const DartFactory&) = delete;				// Prevent copy-construction
	DartFactory& operator=(const DartFactory&) = delete;	// Prevent assignment
	~DartFactory() = default;											// Only this class can delete

	static DartFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (ptrInstance == nullptr)
			ptrInstance = new DartFactory();
		return *ptrInstance;
	};

	DartObjectPool myDartPool;  // Back to be a non-static member instance

	//Store a reference to the live dart to know when the blaster can fire
	//Initialized to nullptr so that the check will pass upon first fire
	Dart* dartRef;

	//The command to pass to the sound manager to play a sound on death
	SoundCommand* pSound;

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time. Not done for this demo however

	// Private NON_STATIC methods to perform actual work on member var
	void privCreateDart(sf::Vector2f pos);
	void privRecycleDart(GameObject* _dartRef);

	void privSendSoundCommand();

	void privStoreSoundCommand();
	

public:

	// Services/API as STATIC METHODS
	//    Usually just a pass-through arguments to private instance methods
	static void CreateDart(sf::Vector2f pos) { Instance().privCreateDart(pos); };
	static void RecycleDart(GameObject* b) { Instance().privRecycleDart(b); };

	static void SendSoundCommand() { Instance().privSendSoundCommand(); };

	static void StoreSoundCommand() { Instance().privStoreSoundCommand(); };

	static void Terminate();
};


#endif _DartFactory