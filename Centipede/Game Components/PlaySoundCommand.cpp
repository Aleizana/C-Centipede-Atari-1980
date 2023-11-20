#include "PlaySoundCommand.h"
#include <iostream>
#include "SoundManager.h"
#include "GameManager.h"

PlaySoundCommand::~PlaySoundCommand()
{
	delete mySound;
}

PlaySoundCommand::PlaySoundCommand(sf::Sound* soundToPlay)
	: mySound(soundToPlay)
{
}

void PlaySoundCommand::Execute()
{
	printf("\tExecuting Play Sound Command\n");
	mySound->play();
}
