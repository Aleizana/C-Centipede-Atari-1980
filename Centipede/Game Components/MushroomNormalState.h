#ifndef _MushroomNormalState
#define _MushroomNormalState

#include "MushroomState.h"
#include "TEAL/CommonElements.h"

class MushroomNormalState : public MushroomState
{

public:
	MushroomNormalState() = default;
	MushroomNormalState(const MushroomNormalState&) = delete;
	MushroomNormalState& operator=(const MushroomNormalState&) = delete;
	virtual ~MushroomNormalState() = default;

	virtual const MushroomState* SwapToOtherState() const override;
	virtual void SetSpriteFromState(Mushroom* mushToChange) const override;
	virtual void SendDeathScoreCommand() const override;
	virtual const sf::IntRect GetSpriteRectFromState(Mushroom* mushToRef) const override;

private:

};

#endif