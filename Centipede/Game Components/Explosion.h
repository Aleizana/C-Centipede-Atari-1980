#ifndef _Explosion
#define _Explosion

#include "TEAL\CommonElements.h"
#include "DisplayOnDeath.h"

class Explosion : public DisplayOnDeath
{
public:
	Explosion();
	Explosion& operator=(const Explosion&) = delete;
	Explosion(Explosion& _copyExplosion) = delete;
	~Explosion() = default;

	virtual void Initialize(sf::Vector2f p, bool plrDeath, float scalar = 1.0f);
	virtual void InitializeWithScore(sf::Vector2f p, int score);

	virtual void Draw();
	virtual void Update();
	virtual void Destroy();


private:
	sf::Vector2f Pos;

	AnimatedSprite ExplosionSprite;

	CollisionTools::TextureBitmap* bitmap;

	//Variables related to the initialization and animation of the sprite from a sprite sheet
	const int ExplosionSpriteFirstFrame = 0;		//For setting the animation of the sprite given the different sprites in the sheet
	const int ExplosionSpriteLastFrame = 7;		//For setting the animation of the sprite given the different sprites in the sheet
	const float spriteOriginSizeDivisor = 2.0f;		//Determines where the (0,0) position of the sprite will be given the size of the texture rectangle
	const float ExplosionScalar = ScalarNumerator / spriteOriginSizeDivisor;		//Set the size of the explosion

	bool plrDeathHold;
	
};

#endif 