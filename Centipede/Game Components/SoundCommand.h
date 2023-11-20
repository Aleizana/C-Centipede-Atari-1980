#ifndef _SoundCommand
#define _SoundCommand

#include "TEAL\CommonElements.h"

class SoundCommand
{
public:
	SoundCommand() = default;
	SoundCommand(const SoundCommand&) = delete;
	SoundCommand& operator=(const SoundCommand&) = delete;
	virtual ~SoundCommand() = default;

	// Note: the Excecute method must NOT have _any_ paramters
	virtual void Execute() = 0;
};

#endif