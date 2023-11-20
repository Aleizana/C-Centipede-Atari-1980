#include "LoopSoundCommand.h"
#include <iostream>
#include "SoundManager.h"
#include "GameManager.h"

LoopSoundCommand::~LoopSoundCommand()
{
	delete mySound;
}

LoopSoundCommand::LoopSoundCommand(sf::Sound* soundToPlay)
	: mySound(soundToPlay)
{
}

void LoopSoundCommand::StopLoop()
{
	mySound->stop();
}

void LoopSoundCommand::Execute()
{
	printf("\tExecuting Loop Sound Command\n");
	//GameManager::GetSoundManager()->AddSound(mySound);
	mySound->play();
}
