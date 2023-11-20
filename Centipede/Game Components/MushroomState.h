#ifndef _MushroomState
#define _MushroomState

#include "TEAL\CommonElements.h"

class Mushroom;
class MushroomPoisonedState;
class MushroomNormalState;

class MushroomState
{
public:
	MushroomState() = default;
	MushroomState(const MushroomState&) = delete;
	MushroomState& operator=(const MushroomState&) = delete;
	virtual ~MushroomState() = default;

	virtual const MushroomState* SwapToOtherState() const = 0;
	virtual void SetSpriteFromState(Mushroom* mushToChange) const = 0;
	virtual void SendDeathScoreCommand() const = 0;
	virtual const sf::IntRect GetSpriteRectFromState(Mushroom* mushToRef) const = 0;

	static const MushroomPoisonedState poisonedState;
	static const MushroomNormalState normalState;

protected:
	const int spriteRectWidth = 16;
	const int spriteRectHeight = 16;
	const int spriteRectInitLeft = 0;
	const int spriteRectInitTop = 0;

	//Represents the number of pixels needed to offset the origin of the rectangle used to grab a singular sprite from the sprite sheet
	const int changeSpriteInSheet = 16;

	
};

#endif