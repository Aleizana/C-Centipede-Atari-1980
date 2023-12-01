#include "SoundManager.h"
#include "PlayerManager.h"
#include "Player.h"
#include "LoopSoundCommand.h"
#include "SoundCommand.h"
#include "PlaySoundCommand.h"
#include <iostream>
#include "TEAL\CommonElements.h"
#include "SoundStrategy.h"
#include "PlaySoundStrategy.h"
#include "MutedSoundStrategy.h"
#include "GameManager.h"

const PlaySoundStrategy SoundManager::playStrategy;
const MutedSoundStrategy SoundManager::muteStrategy;

SoundManager::SoundManager()
	: currStrategy((SoundStrategy*)&SoundManager::muteStrategy)
{
}

SoundCommand* SoundManager::GetSoundCommand(SoundEvents ev)
{

	SoundCommand* pCmd = nullptr;
	sf::Sound* soundHold;

	ConsoleMsg::WriteLine("Sound Manager: Constructing Sound command for ");

	switch (ev)
	{
	case SoundEvents::BlasterDeath:
		ConsoleMsg::WriteLine("\tBlaster Death");

		soundHold = new sf::Sound();
		soundHold->setBuffer(ResourceManager::GetSound("BlasterDeath"));
		soundHold->setPitch(2);
		soundHold->setVolume(2);

		pCmd = new PlaySoundCommand(soundHold);
		break;
	case SoundEvents::FireDart:
		ConsoleMsg::WriteLine("\tFiring a Dart");

		soundHold = new sf::Sound();
		soundHold->setBuffer(ResourceManager::GetSound("FireDart"));
		soundHold->setPitch(2);
		soundHold->setVolume(1);

		pCmd = new PlaySoundCommand(soundHold);

		break;
	case SoundEvents::FleaFall:
		ConsoleMsg::WriteLine("\tFlea Movement Loop");

		soundHold = new sf::Sound();
		soundHold->setBuffer(ResourceManager::GetSound("FleaMovement"));
		soundHold->setPitch(2);
		soundHold->setVolume(1);

		pCmd = new LoopSoundCommand(soundHold);
		break;
	case SoundEvents::ScorpionLoop:
		ConsoleMsg::WriteLine("\tScorpion Movement Loop");

		soundHold = new sf::Sound();
		soundHold->setBuffer(ResourceManager::GetSound("ScorpionMovement"));
		soundHold->setPitch(2);
		soundHold->setVolume(1);
		soundHold->setLoop(true);

		pCmd = new LoopSoundCommand(soundHold);
		break;
	case SoundEvents::SpiderLoop:
		ConsoleMsg::WriteLine("\tSpider Movement Loop");

		soundHold = new sf::Sound();
		soundHold->setBuffer(ResourceManager::GetSound("SpiderMovement"));
		soundHold->setPitch(2);
		soundHold->setVolume(1);
		soundHold->setLoop(true);

		pCmd = new LoopSoundCommand(soundHold);
		break;
	case SoundEvents::ExtraLife:
		ConsoleMsg::WriteLine("\tExtra Life");

		soundHold = new sf::Sound();
		soundHold->setBuffer(ResourceManager::GetSound("ExtraLife"));
		soundHold->setPitch(2);
		soundHold->setVolume(2);

		pCmd = new PlaySoundCommand(soundHold);
		break;
	case SoundEvents::NonPlayerDeath:
		ConsoleMsg::WriteLine("\tDeath of a Non-Player");

		soundHold = new sf::Sound();
		soundHold->setBuffer(ResourceManager::GetSound("NonPlayerDeath"));
		soundHold->setPitch(2);
		soundHold->setVolume(2);

		pCmd = new PlaySoundCommand(soundHold);
		break;
	case SoundEvents::CentipedeLoop:
		ConsoleMsg::WriteLine("\tCentipede Movement Loop");

		soundHold = new sf::Sound();
		soundHold->setBuffer(ResourceManager::GetSound("CentipedeMovement"));
		soundHold->setPitch(2);
		soundHold->setVolume(1);
		soundHold->setLoop(true);

		pCmd = new LoopSoundCommand(soundHold);
		break;
	case SoundEvents::MushroomRegen:
		ConsoleMsg::WriteLine("\tMushroom Regeneration");

		soundHold = new sf::Sound();
		soundHold->setBuffer(ResourceManager::GetSound("MushroomRegen"));
		soundHold->setPitch(2);
		soundHold->setVolume(2);

		pCmd = new PlaySoundCommand(soundHold);
		break;
	default:
		ConsoleMsg::WriteLine("\t<nothing>");
		break;
	}

	return pCmd;
}

void SoundManager::SendSoundCmd(SoundCommand* c)
{
	QueueCmds.push(c);
}

void SoundManager::ProcessSounds()
{
	//Put "isMuted" boolean here
	privProcessSound();
}

void SoundManager::Unmute()
{
	currStrategy = (SoundStrategy*)&SoundManager::playStrategy;
}

void SoundManager::ToggleMute()
{
	currStrategy = currStrategy->SwapToOtherStrategy();
}



void SoundManager::privProcessSound()
{
	if (!QueueCmds.empty())
	{
		ConsoleMsg::WriteLine("Processing all Sounds commands for this frame:");
	}

	SoundCommand* c;

	while (!QueueCmds.empty())
	{
		c = QueueCmds.front();

		//Pass the sound to the current sound strategy for execution
		currStrategy->ExecuteSound(c);

		QueueCmds.pop();
	}
}
