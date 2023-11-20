#ifndef _MushroomRegeneration
#define _MushroomRegeneration

#include "TEAL\CommonElements.h"
#include <stack>

class Mushroom;
class Scene;

class MushroomRegeneration : public GameObject
{
public:
	MushroomRegeneration() = default;
	MushroomRegeneration(MushroomRegeneration& copyMushroomRegeneration) = delete;
	MushroomRegeneration& operator=(MushroomRegeneration&) = delete;
	~MushroomRegeneration() = default;

	MushroomRegeneration(std::stack<Mushroom*> dmgStack, Scene* sceneToStart, bool playerSwap);

private:
	//For spawning performing spaced out mushroom regeneration
	virtual void Alarm3();

	//For setting the alarm number and timer of individual regen animations
	const int alarmNum = 3;
	const float alarmTimer = 0.3f;

	//For checking what the size of the stack should be after the last animation. This stops the alarm from being called again.
	const int lastAnimationCheck = 1;

	//Holds the mushrooms that need to be regenerated
	std::stack<Mushroom*> mushroomStack;

	//Holds the scene that will begin once regeneration has completed
	Scene* holdSceneToStart;

	//For the mushroom regenerator to know when there are no more mushrooms and restarting the alarm can end
	bool startScene;

	//To know when a player swap needs to happen after mushroom regeneration has concluded
	bool plrSwap;

};

#endif