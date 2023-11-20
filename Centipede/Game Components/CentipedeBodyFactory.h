// CentipedeBodyFactory
// Andre Berthiaume, April 2013

#ifndef _CentipedeBodyFactory
#define _CentipedeBodyFactory

#include "CentipedeBodyObjectPool.h"
#include "SFML/Graphics.hpp"
class GameObject;

//To store a reference to the created CentipedeBody to know when the blaster can fire
class CentipedeBody;
class CentipedeBodyMover;
class CentipedeHead;
class CmdScore;
//class SoundCommand;

class CentipedeBodyFactory
{
private:
	/******************************************************************
			  Currecctly set-up as a Singleton
	********************************************************************/
	static CentipedeBodyFactory* ptrInstance;			// Game set up as a singleton

	CentipedeBodyFactory();												// Private constructor
	CentipedeBodyFactory(const CentipedeBodyFactory&) = delete;				// Prevent copy-construction
	CentipedeBodyFactory& operator=(const CentipedeBodyFactory&) = delete;	// Prevent assignment
	~CentipedeBodyFactory() = default;											// Only this class can delete

	static CentipedeBodyFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (ptrInstance == nullptr)
			ptrInstance = new CentipedeBodyFactory();
		return *ptrInstance;
	};

	CentipedeBodyObjectPool myCentipedeBodyPool;  // Back to be a non-static member instance

	//The command to pass to the score manager to calculate the points for kill
	CmdScore* pDeath;

	//For storing the number of centipede body's present on the screen
	int bodyCount;

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time. Not done for this demo however

	// Private NON_STATIC methods to perform actual work on member var
	CentipedeBody* privCreateCentipedeBody(sf::Vector2f pos, int row, int col, CentipedeHead* _head, CentipedeBody* _prevBody, float speed);
	void privRecycleCentipedeBody(GameObject* _CentipedeBodyRef);

	//For centi bodies to tell the factory to send the death command for scoring upon death
	void privSendDeathCommandForScore();

	int privGetBodyCount();

	void privResetBodyCount();

	void privDecrementBodyCount();


public:

	// Services/API as STATIC METHODS
	//    Usually just a pass-through arguments to private instance methods
	static CentipedeBody* CreateCentipedeBody(sf::Vector2f pos, int row, int col, CentipedeHead* _head, CentipedeBody* _prevBody, float speed) { 
		return Instance().privCreateCentipedeBody(pos, row, col, _head, _prevBody, speed); };
	static void RecycleCentipedeBody(GameObject* b) { Instance().privRecycleCentipedeBody(b); };

	static int GetBodyCount() { return Instance().privGetBodyCount(); };

	static void ResetBodyCount() { return Instance().privResetBodyCount(); };

	static void DecrementBodyCount() { Instance().privDecrementBodyCount(); };

	static void Terminate();

	static void SendDeathCommandForScore() { Instance().privSendDeathCommandForScore(); };
};


#endif _CentipedeBodyFactory