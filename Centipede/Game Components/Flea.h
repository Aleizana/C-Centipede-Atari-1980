#pragma once
#ifndef _Flea
#define _Flea

#include "TEAL\CommonElements.h"

//Note: Forward declare to avoid include - loop since Dart.h includes Flea.h
class Dart;
class FleaMover;

class Flea : public GameObject
{
public:
	Flea();
	Flea(Flea& copyFlea) = delete;
	Flea& operator=(Flea&) = delete;
	~Flea() = default;

	void Initialize(sf::Vector2f p, FleaMover* _moverRef);

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision(GameObject* go) {};

	//The dart will cause the Flea to lose 1 health, and the dart will then destroy itself
	virtual void Collision(Dart* other);

	//Set the row and column of the Flea
	void SetRowCol(int row, int col);

	//Get the row or the col of the flea
	int GetMyRow();
	int GetMyCol();

	//Set the row of the flea
	void SetMyRow(int newRow);

	//Set the position of the flea
	void SetMyPos(sf::Vector2f _newPos);

	//Get the position of the flea
	sf::Vector2f GetMyPos();

	//Returns the current health of the flea
	int GetMyHealth();

	//Flea game properties
	static const int FleaSpawnHealth = 2;

	float GetSpeed();
	void SetSpeedThroughMulitplier(float multiplier);

private:
	sf::Vector2f Pos;
    AnimatedSprite FleaSprite;
	CollisionTools::TextureBitmap* bitmap;

	//The Flea will store it's grid position
	int fleaRow;
	int fleaCol;

	//Variables related to the initialization and animation of the sprite from a sprite sheet
	const int fleaFrameCountWidth = 2;		//Number of sprites that will be cycled through in each row
	const int fleaFrameCountHeight = 2;		//Number of sprites that will be cycled through in each column
	const float fleaSpriteFPS = 15.0f;		//Frame speed at which the sprites will be cycled through
	const int fleaSpriteFirstFrame = 0;		//For setting the animation of the sprite given the different sprites in the sheet
	const int fleaSpriteLastFrame = 3;		//For setting the animation of the sprite given the different sprites in the sheet
	const float spriteOriginSizeDivisor = 3.0f;		//Determines where the (0,0) position of the sprite will be given the size of the texture rectangle

	//Reference to the flea mover that will handle movement for the flea
	FleaMover* myMoverRef;

	float currSpeed;

	int countMovement;
};

#endif