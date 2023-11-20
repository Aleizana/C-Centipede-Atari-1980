#pragma once
#ifndef _Spider
#define _Spider

#include "TEAL\CommonElements.h"
#include "SpiderFactory.h"		//Necessary for the use of its directional enum

//Note: Forward declare to avoid include - loop since Dart.h includes Spider.h
class Dart;
class SpiderMover;
class SpiderMoveState;

class Spider : public GameObject
{
public:
	Spider();
	Spider(Spider& copySpider) = delete;
	Spider& operator=(Spider&) = delete;
	~Spider() = default;

	void Initialize(sf::Vector2f p, SpiderMover* _moverRef, SpiderFactory::SpiderMainDirection newDir);

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision(GameObject* go) {};

	//The dart will cause the Spider to lose 1 health, and the dart will then destroy itself
	virtual void Collision(Dart* other);

	//Set the row and column of the Spider
	void SetRowCol(int row, int col);

	//Get the row or the col of the Spider
	int GetMyRow();
	int GetMyCol();

	//Set the row of the Spider
	void SetMyRow(int newRow);

	//Set the position of the Spider
	void SetMyPos(sf::Vector2f _newPos);

	//Get the position of the Spider
	sf::Vector2f GetMyPos();

	SpiderFactory::SpiderMainDirection GetSpiderDir();

	const SpiderMoveState* GetMyState();
	void GetNextState();

private:
	sf::Vector2f Pos;
	AnimatedSprite SpiderSprite;
	CollisionTools::TextureBitmap* bitmap;

	//The Spider will store it's grid position
	int SpiderRow;
	int SpiderCol;

	//Variables related to the initialization and animation of the sprite from a sprite sheet
	const int SpiderFrameCountWidth = 4;		//Number of sprites that will be cycled through in each row
	const int SpiderFrameCountHeight = 2;		//Number of sprites that will be cycled through in each column
	const float SpiderSpriteFPS = 15.0f;		//Frame speed at which the sprites will be cycled through
	const int SpiderSpriteFirstFrame = 0;		//For setting the animation of the sprite given the different sprites in the sheet
	const int SpiderSpriteLastFrame = 7;		//For setting the animation of the sprite given the different sprites in the sheet
	const float spriteOriginSizeDivisor = 2.0f;		//Determines where the (0,0) position of the sprite will be given the size of the texture rectangle

	//Scale the spider
	const float SpiderScalar = 2.0f;

	//Reference to the Spider mover that will handle movement for the Spider
	SpiderMover* myMoverRef;

	//Spider game properties
	static const int SpiderSpawnHealth = 2;

	//Move array index
	int moveArrIncrementor;

	//Enum value for the spider to move in a set horizontal direction
	SpiderFactory::SpiderMainDirection currSpiderDir;

	//Movement offset and state for spider
	const SpiderMoveState* pCurrMoveState;
};

#endif