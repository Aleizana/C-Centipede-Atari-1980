#ifndef _PlaySoundStrategy
#define _PlaySoundStrategy

#include "SoundStrategy.h"
#include "TEAL/CommonElements.h"

class SoundCommand;

class PlaySoundStrategy : public SoundStrategy
{

public:
	PlaySoundStrategy() = default;
	PlaySoundStrategy(const PlaySoundStrategy&) = delete;
	PlaySoundStrategy& operator=(const PlaySoundStrategy&) = delete;
	virtual ~PlaySoundStrategy() = default;

	virtual void ExecuteSound(SoundCommand* soundToPlay) const  override;
	virtual const SoundStrategy* SwapToOtherStrategy() const override;
};

#endif