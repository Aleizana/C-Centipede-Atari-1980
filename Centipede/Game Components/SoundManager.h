#ifndef _SoundManager
#define _SoundManager

#include <queue>

#include "TEAL/CommonElements.h"

class SoundCommand;
class SoundStrategy;
class MutedSoundStrategy;
class PlaySoundStrategy;

class SoundManager
{
private:
	std::queue<SoundCommand*> QueueCmds;

	

	const SoundStrategy* currStrategy;

	void privProcessSound();

public:
	// events
	enum SoundEvents { BlasterDeath, FireDart, FleaFall, ScorpionLoop, SpiderLoop, ExtraLife, NonPlayerDeath, CentipedeLoop, MushroomRegen };

	void AddSound(sf::Sound* playSound);

	SoundCommand* GetSoundCommand(SoundEvents ev);

	void SendSoundCmd(SoundCommand* c);
	void ProcessSounds();

	void ToggleMute();

	SoundManager();
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;
	virtual ~SoundManager() = default;

	static const MutedSoundStrategy muteStrategy;
	static const PlaySoundStrategy playStrategy;

};

#endif