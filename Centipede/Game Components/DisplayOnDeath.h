#ifndef _DisplayOnDeath
#define _DisplayOnDeath

#include "TEAL\CommonElements.h"

class DisplayOnDeath : public GameObject
{
public:
	DisplayOnDeath() = default;
	DisplayOnDeath& operator=(const DisplayOnDeath&) = delete;
	DisplayOnDeath(DisplayOnDeath& _copyDisplayOnDeath) = delete;
	~DisplayOnDeath() = default;

	virtual void Initialize(sf::Vector2f p, bool plrDeath, float scalar = 1.0f) = 0;
	virtual void InitializeWithScore(sf::Vector2f p, int score) = 0;

	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;


protected:
	sf::Vector2f Pos;

	CollisionTools::TextureBitmap* bitmap = nullptr;

	//Variables related to the initialization and animation of the sprite from a sprite sheet
	const int DisplayOnDeathFrameCountWidth = 4;		//Number of sprites that will be cycled through in each row
	const int DisplayOnDeathFrameCountHeight = 2;		//Number of sprites that will be cycled through in each column
	const float DisplayOnDeathSpriteFPS = 0.50f;		//Frame speed at which the sprites will be cycled through
	const int ScalarNumerator = 1;

	const int DisplayOnDeathDrawOrder = 10000;

	//To know when the animation for the DisplayOnDeath has ended
	int countSpriteFrames = 0;
	const int EndSprite = DisplayOnDeathFrameCountWidth * DisplayOnDeathFrameCountHeight;
	int spriteEndFrameOffset = 0;

};

#endif 