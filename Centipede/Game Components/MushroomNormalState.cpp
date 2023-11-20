#include "MushroomNormalState.h"
#include "Mushroom.h"
#include "MushroomFactory.h"

const MushroomState* MushroomNormalState::SwapToOtherState() const
{
	return (MushroomState*)&MushroomState::poisonedState;
}

void MushroomNormalState::SetSpriteFromState(Mushroom* mushToChange) const
{
	int mushStartingHP = mushToChange->GetStartingHP();
	int dmgTaken = mushStartingHP - mushToChange->GetMyHealth();
	mushToChange->GetSprite().setTextureRect(sf::IntRect(spriteRectInitLeft + (dmgTaken * changeSpriteInSheet), spriteRectInitTop, spriteRectWidth, spriteRectHeight));
}

void MushroomNormalState::SendDeathScoreCommand() const
{
	MushroomFactory::SendDeathCommandForScore_NoPoison();
}

const sf::IntRect MushroomNormalState::GetSpriteRectFromState(Mushroom* mushToRef) const
{
	int mushStartingHP = mushToRef->GetStartingHP();
	int dmgTaken = mushStartingHP - mushToRef->GetMyHealth();

	return sf::IntRect(spriteRectInitLeft + (dmgTaken * changeSpriteInSheet), spriteRectInitTop, spriteRectWidth, spriteRectHeight);
}
