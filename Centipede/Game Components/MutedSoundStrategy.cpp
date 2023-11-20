#include "MutedSoundStrategy.h"
#include "SoundCommand.h"
#include "SoundManager.h"
#include "GameManager.h"

void MutedSoundStrategy::ExecuteSound(SoundCommand* soundToPlay) const
{
	//Do nothing, as this strategy is used for muting all sounds
}

const SoundStrategy* MutedSoundStrategy::SwapToOtherStrategy() const
{
	GameManager::NotifyFactoriesToSendLoopedSounds_OnUnmute();
	return (SoundStrategy*)&SoundManager::playStrategy;
}
