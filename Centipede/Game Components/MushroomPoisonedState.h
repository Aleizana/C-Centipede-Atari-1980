#ifndef _MushroomPoisonedState
#define _MushroomPoisonedState

#include "MushroomState.h"
#include "TEAL/CommonElements.h"

class MushroomPoisonedState : public MushroomState
{

public:
	MushroomPoisonedState() = default;
	MushroomPoisonedState(const MushroomPoisonedState&) = delete;
	MushroomPoisonedState& operator=(const MushroomPoisonedState&) = delete;
	virtual ~MushroomPoisonedState() = default;

	virtual const MushroomState* SwapToOtherState() const override;
	virtual void SetSpriteFromState(Mushroom* mushToChange) const override;
	virtual void SendDeathScoreCommand() const override;
	virtual const sf::IntRect GetSpriteRectFromState(Mushroom* mushToRef) const override;

private:
	//Represents the number of pixels needed to offset the origin of the rectangle used to grab a singular sprite from the sprite sheet
	const int changeSpriteInSheet = 16;
};

#endif