#ifndef _CentiBase
#define _CentiBase

#include "TEAL\CommonElements.h"

//Foward declare for reference to CentipedeBaseMover class
class Dart;
class Blaster;
class MoveState;
class CentipedeBody;

class CentipedeBase : public GameObject
{
public:
	CentipedeBase() = default;
	CentipedeBase(const CentipedeBase& copyHead) = delete;
	CentipedeBase& operator=(const CentipedeBase&) = delete;
	~CentipedeBase() = default;

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;

	virtual void Collision(GameObject* other) {};

	virtual void Collision(Dart* other) = 0;

	//To manually queue a movement state for the centipede head
	virtual void SetMoveState_FSM(const MoveState* newState) = 0;


protected:
	//The draw order priority of the centipede head sprite
	const int CentiDrawOrder = 1000;

	const int CentipedeSpawnHealth = 1;

	//To hold the current speed of the centipede
	float holdSpeed;

	//The centipede will store it's own row and column to be referenced by other classes such as the HeadMover
	int myRow;
	int myCol;

	//Sprite for the head, will need to make it animated later
	AnimatedSprite CentiSprite;

	//Variables related to the initialization and animation of the sprite from a sprite sheet
	const int SpriteFrameCountWidth = 8;		//Number of sprites that will be cycled through in each row
	const int SpriteFrameCountHeight = 2;		//Number of sprites that will be cycled through in each column
	const float SpriteFPS = 15.0f;		//Frame speed at which the sprites will be cycled through
	const float SpriteInitScale = 2.0f;	//For scaling the size of the sprite
	int SpriteFirstFrame;		//For setting the animation of the sprite given the different sprites in the sheet
	int SpriteLastFrame;		//For setting the animation of the sprite given the different sprites in the sheet
	float SpriteFlip_X;		//For flipping the direction of the sprite
	float SpriteFlip_Y;		//For flipping the direction of the sprite
	const float spriteOriginDiv = 2.0f;		//Determines where the (0,0) position of the sprite will be given the size of the texture rectangle

	//Collision map
	CollisionTools::TextureBitmap bitmap;

	//Position of the centipede head
	sf::Vector2f Pos;

	//For holding the current movement state/pattern/direction of the centipede
	const MoveState* pCurrentState;

	//Holds the movement state when a new centipede is created from a body part
	const MoveState* pHoldState;

	//For counting the number of frames in which the centipede has moved
	int incrementMoveArray;

	//The amount by which the head will move through the offset array indices
	int incrementMoveArrayAmount;

	//Pointer to the start of the linked-list of bodies
	//CentipedeBody* bodyFirstNode;

	virtual void privCreateMushroomFromBody() = 0;

	virtual void privOnDeathCreateHead() = 0;

	virtual void UpdateSpriteValuesFromState() = 0;
};

#endif