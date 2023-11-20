#ifndef _PlaySoundCommand
#define _PlaySoundCommand

#include "SoundCommand.h"
#include "TEAL/CommonElements.h"

class PlaySoundCommand : public SoundCommand
{
protected:
	sf::Sound* mySound;

public:
	PlaySoundCommand() = delete;
	PlaySoundCommand(const PlaySoundCommand&) = delete;
	PlaySoundCommand& operator=(const PlaySoundCommand&) = delete;
	virtual ~PlaySoundCommand();

	PlaySoundCommand(sf::Sound* soundToPlay);

	virtual void Execute() override;
};

#endif