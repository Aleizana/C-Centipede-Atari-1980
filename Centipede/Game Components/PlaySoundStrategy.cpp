#include "PlaySoundStrategy.h"
#include "SoundCommand.h"
#include "SoundManager.h"
#include "GameManager.h"

void PlaySoundStrategy::ExecuteSound(SoundCommand* soundToPlay) const
{
	//Play the sound command
	soundToPlay->Execute();
}

const SoundStrategy* PlaySoundStrategy::SwapToOtherStrategy() const
{
	GameManager::NotifyFactoriesToStopLoopedSounds_OnMute();
	return (SoundStrategy*)&SoundManager::muteStrategy;
}
