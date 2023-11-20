// ExplosionFactory
// Andre Berthiaume, April 2013

#ifndef _ExplosionFactory
#define _ExplosionFactory

#include "ExplosionObjectPool.h"
#include "SFML/Graphics.hpp"
class GameObject;

//To store a reference to the created Explosion to know when the blaster can fire
class Explosion;

class ExplosionFactory
{
private:
	/******************************************************************
			  Currecctly set-up as a Singleton
	********************************************************************/
	static ExplosionFactory* ptrInstance;			// Game set up as a singleton

	ExplosionFactory() = default;												// Private constructor
	ExplosionFactory(const ExplosionFactory&) = delete;				// Prevent copy-construction
	ExplosionFactory& operator=(const ExplosionFactory&) = delete;	// Prevent assignment
	~ExplosionFactory() = default;											// Only this class can delete

	static ExplosionFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (ptrInstance == nullptr)
			ptrInstance = new ExplosionFactory();
		return *ptrInstance;
	};

	ExplosionObjectPool myExplosionPool;  // Back to be a non-static member instance

	//Store a reference to the live Explosion to know when the blaster can fire
	//Initialized to nullptr so that the check will pass upon first fire
	Explosion* ExplosionRef = nullptr;

	//Tells the explosion to divide the width of the explosion by 2 so that it can be 1by1
	float scalar1By1 = 2.0f;

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time. Not done for this demo however

	// Private NON_STATIC methods to perform actual work on member var
	void privCreateExplosion1By1(sf::Vector2f pos, bool plrDeath = false);
	void privCreateExplosion2By1(sf::Vector2f pos, bool plrDeath = false);
	void privRecycleExplosion(GameObject* _ExplosionRef);

public:

	// Services/API as STATIC METHODS
	//    Usually just a pass-through arguments to private instance methods
	static void CreateExplosion1By1(sf::Vector2f pos) { Instance().privCreateExplosion1By1(pos); };
	static void CreateExplosionPlayerDeath(sf::Vector2f pos) { Instance().privCreateExplosion2By1(pos, true); };
	static void RecycleExplosion(GameObject* b) { Instance().privRecycleExplosion(b); };

	static void Terminate();
};


#endif _ExplosionFactory