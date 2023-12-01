// ScoreDisplayOnDeath

#include "ScoreDisplayOnDeath.h"
#include "DisplayOnDeathFactory.h"
#include "GameManager.h"
#include "ScoreManager.h"

ScoreDisplayOnDeath::ScoreDisplayOnDeath()
	: spriteRectInitTop(0)
{
	SetDrawOrder(DisplayOnDeathDrawOrder);
}

void ScoreDisplayOnDeath::Initialize(sf::Vector2f p, bool plrDeath, float scalar)
{
	//do nothing
}

void ScoreDisplayOnDeath::InitializeWithScore(sf::Vector2f p, int score)
{
	Pos = p;

	if (score == GameManager::GetScoreMgr()->GetCloseSpiderScore())
	{
		spriteRectInitTop = SpriteOffsetForThirdRow;
	}
	else if (score == GameManager::GetScoreMgr()->GetMedSpiderScore())
	{
		spriteRectInitTop = SpriteOffsetForSecondRow;
	}
	//First row of sprite sheet for far spider score
	else
	{
		spriteRectInitTop = SpriteOffsetForFirstRow;
	}

	sf::IntRect holdSpriteRect = sf::IntRect(spriteRectInitLeft, spriteRectInitTop, spriteRectWidth, spriteRectHeight);

	ScoreSprite = sf::Sprite(ResourceManager::GetTexture("FullSpriteList"), holdSpriteRect);

	ScoreSprite.setPosition(Pos);

	ScoreSprite.scale(ScoreSpriteScalar, ScoreSpriteScalar);

	//Set the origin (0,0) of the sprite
	ScoreSprite.setOrigin((float)ScoreSprite.getTextureRect().width / ScoreSpriteScalar, (float)ScoreSprite.getTextureRect().height / ScoreSpriteScalar);

	countSpriteFrames = 0;

	spriteEndFrameOffset = (int)(EndSprite / DisplayOnDeathSpriteFPS);
}

void ScoreDisplayOnDeath::Update()
{
	//You HAVE to do this every update or else the position will go to (0,0)
	ScoreSprite.setPosition(Pos);

	countSpriteFrames++;

	//Once the ScoreDisplayOnDeath animation is over, destroy the ScoreDisplayOnDeath
	if (countSpriteFrames == spriteEndFrameOffset)
	{
		//Recycle this ScoreDisplayOnDeath object
		MarkForDestroy();
	}
}

void ScoreDisplayOnDeath::Draw()
{
	WindowManager::Window().draw(ScoreSprite);
}



void ScoreDisplayOnDeath::Destroy()
{
	ConsoleMsg::WriteLine("Deleted ScoreDisplayOnDeath!");
}