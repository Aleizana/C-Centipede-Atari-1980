#ifndef _MutedSoundStrategy
#define _MutedSoundStrategy

#include "SoundStrategy.h"
#include "TEAL/CommonElements.h"

class SoundCommand;

class MutedSoundStrategy : public SoundStrategy
{

public:
	MutedSoundStrategy() = default;
	MutedSoundStrategy(const MutedSoundStrategy&) = delete;
	MutedSoundStrategy& operator=(const MutedSoundStrategy&) = delete;
	virtual ~MutedSoundStrategy() = default;

	virtual void ExecuteSound(SoundCommand* soundToPlay) const override;
	virtual const SoundStrategy* SwapToOtherStrategy() const override;
};

#endif