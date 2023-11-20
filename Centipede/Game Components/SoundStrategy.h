#ifndef _SoundStrategy
#define _SoundStrategy

#include "TEAL\CommonElements.h"

class SoundCommand;

class SoundStrategy
{
public:
	SoundStrategy() = default;
	SoundStrategy(const SoundStrategy&) = delete;
	SoundStrategy& operator=(const SoundStrategy&) = delete;
	virtual ~SoundStrategy() = default;

	virtual void ExecuteSound(SoundCommand* soundToPlay) const = 0;
	virtual const SoundStrategy* SwapToOtherStrategy() const = 0;
};

#endif