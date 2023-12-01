// Explosion

#include "Explosion.h"
#include "DisplayOnDeathFactory.h"
#include "GameManager.h"

Explosion::Explosion()
	: bitmap(nullptr), plrDeathHold(false)
{

	SetDrawOrder(DisplayOnDeathDrawOrder);
}

void Explosion::Initialize(sf::Vector2f p, bool plrDeath, float scalar)
{
	Pos = p;

	ExplosionSprite = AnimatedSprite(ResourceManager::GetTexture("explosion"), DisplayOnDeathFrameCountWidth, DisplayOnDeathFrameCountHeight, DisplayOnDeathSpriteFPS);

	ExplosionSprite.setPosition(Pos);

	//Sets the first and the last frame of the sprite sheet
	ExplosionSprite.SetAnimation(ExplosionSpriteFirstFrame, ExplosionSpriteLastFrame);

	ExplosionSprite.scale((float)((float)ScalarNumerator / scalar), (float)ScalarNumerator);

	//Set the origin (0,0) of the sprite
	ExplosionSprite.setOrigin((float)ExplosionSprite.getTextureRect().width / scalar, (float)ExplosionSprite.getTextureRect().height / scalar);

	countSpriteFrames = 0;

	spriteEndFrameOffset = (int)(EndSprite / DisplayOnDeathSpriteFPS);

	plrDeathHold = plrDeath;
}

void Explosion::InitializeWithScore(sf::Vector2f p, int score)
{
	//do nothing
}

void Explosion::Update()
{
	//You HAVE to do this every update or else the position will go to (0,0)
	ExplosionSprite.setPosition(Pos);

	//Update the appearance of the sprite
	ExplosionSprite.Update();

	countSpriteFrames++;

	//Once the explosion animation is over, destroy the explosion
	if (countSpriteFrames >= spriteEndFrameOffset)
	{
		//If toggled, let the game manager the player is dead now that the explosion has completed
		if (plrDeathHold)
		{
			GameManager::NotifyPlayerDeath();
		}

		//Reset the explosion sprite to be reused next explosion
		ExplosionSprite.Reset();

		//Recycle this explosion object
		MarkForDestroy();
	}
}

void Explosion::Draw()
{
	WindowManager::Window().draw(ExplosionSprite);
}



void Explosion::Destroy()
{
	ConsoleMsg::WriteLine("Deleted Explosion!");
}