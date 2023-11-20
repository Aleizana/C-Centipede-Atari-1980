#ifndef _LoopSoundCommand
#define _LoopSoundCommand

#include "SoundCommand.h"
#include "TEAL/CommonElements.h"

class LoopSoundCommand : public SoundCommand
{
protected:
	sf::Sound* mySound;

public:
	LoopSoundCommand() = delete;
	LoopSoundCommand(const LoopSoundCommand&) = delete;
	LoopSoundCommand& operator=(const LoopSoundCommand&) = delete;
	virtual ~LoopSoundCommand();

	LoopSoundCommand(sf::Sound* soundToPlay);

	void StopLoop();

	virtual void Execute() override;
};

#endif