#include "MushroomRegeneration.h"
#include "Mushroom.h"
#include "DisplayOnDeathFactory.h"
#include "MushroomFactory.h"
#include "TEAL/SceneManager.h"
#include "GameManager.h"
#include "PlayerManager.h"

MushroomRegeneration::MushroomRegeneration(std::stack<Mushroom*> dmgStack, Scene* sceneToStart, bool playerSwap)
{
	mushroomStack = dmgStack;

	startScene = false;

	plrSwap = playerSwap;

	if (!mushroomStack.empty())
	{
		holdSceneToStart = sceneToStart;

		//Set the alarm to activate immediately and start processing
		SetAlarm(alarmNum, 0);
	}
	else
	{
		if (plrSwap)
		{
			GameManager::SwapActivePlayer();

			delete sceneToStart;
		}
		else
		{
			//Begin the next scene if the stack is empty
			GameManager::PassSceneToStart(sceneToStart);
		}
	}

	
}

void MushroomRegeneration::Alarm3()
{
	//The separation of these two allows for the final mushroom regeneration animation to play
	if (startScene)
	{
		startScene = false;

		if (plrSwap)
		{
			GameManager::SwapActivePlayer();

			delete holdSceneToStart;
		}
		else
		{
			//Begin the next scene now that mushroom regeneration has completed
			GameManager::PassSceneToStart(holdSceneToStart);
		}
	}
	else
	{
		Mushroom* holdMush = mushroomStack.top();

		//Create an explosion at the position of the mushroom
		DisplayOnDeathFactory::CreateExplosion1By1(holdMush->GetPos());

		//Play the sound for mushroom regeneration
		MushroomFactory::SendSoundCommand();

		//Reset the health, lifestate, and sprite offset of the mushroom
		holdMush->ResetState();

		//Set the alarm to activate immediately and start processing
		SetAlarm(alarmNum, alarmTimer);

		//Check whether the last stack item has been processed
		if (mushroomStack.size() == (size_t)lastAnimationCheck)
		{
			startScene = true;
		}

		mushroomStack.pop();
	}
}
