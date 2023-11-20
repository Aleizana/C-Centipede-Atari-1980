#ifndef _ScoreDisplayOnDeath
#define _ScoreDisplayOnDeath

#include "TEAL\CommonElements.h"
#include "DisplayOnDeath.h"

class ScoreDisplayOnDeath : public DisplayOnDeath
{
public:
	ScoreDisplayOnDeath();
	ScoreDisplayOnDeath& operator=(const ScoreDisplayOnDeath&) = delete;
	ScoreDisplayOnDeath(ScoreDisplayOnDeath& _copyScoreDisplayOnDeath) = delete;
	~ScoreDisplayOnDeath() = default;

	virtual void Initialize(sf::Vector2f p, bool plrDeath, float scalar = 1.0f);
	virtual void InitializeWithScore(sf::Vector2f p, int score);

	virtual void Draw();
	virtual void Update();
	virtual void Destroy();


private:
	sf::Sprite ScoreSprite;

	//The score sprite has a height of 8 pixels to start, we want it to be 16
	const float ScoreSpriteScalar = 2.0f;

	//The score sprites are 16 pixels wide
	const int spriteRectWidth = 16;
	//8 pixels tall
	const int spriteRectHeight = 8;
	//They begin 96 pixels horizontally into the sheet
	const int spriteRectInitLeft = 96;
	//The sprite offset from the top will be determined by the score value to be displayed
	int spriteRectInitTop;

	//Different offsets from the top of the sprite sheet to get the correct sprite representingt the score
	const int SpriteOffsetForFirstRow = 0;
	const int SpriteOffsetForSecondRow = 8;
	const int SpriteOffsetForThirdRow = 16;
};

#endif 