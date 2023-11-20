#include "MushroomPoisonedState.h"
#include "Mushroom.h"
#include "MushroomFactory.h"

const MushroomState* MushroomPoisonedState::SwapToOtherState() const
{
	return (MushroomState*)&MushroomState::normalState;
}

void MushroomPoisonedState::SetSpriteFromState(Mushroom* mushToChange) const
{
	int mushStartingHP = mushToChange->GetStartingHP();
	int dmgTaken = mushStartingHP - mushToChange->GetMyHealth();
	mushToChange->GetSprite().setTextureRect(sf::IntRect(spriteRectInitLeft + (dmgTaken * changeSpriteInSheet), spriteRectInitTop + changeSpriteInSheet, spriteRectWidth, spriteRectHeight));
}

void MushroomPoisonedState::SendDeathScoreCommand() const
{
	MushroomFactory::SendDeathCommandForScore_Poison();
}

const sf::IntRect MushroomPoisonedState::GetSpriteRectFromState(Mushroom* mushToRef) const
{
	int mushStartingHP = mushToRef->GetStartingHP();
	int dmgTaken = mushStartingHP - mushToRef->GetMyHealth();

	return sf::IntRect(spriteRectInitLeft + (dmgTaken * changeSpriteInSheet), spriteRectInitTop + changeSpriteInSheet, spriteRectWidth, spriteRectHeight);
}
