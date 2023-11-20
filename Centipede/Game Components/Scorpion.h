#ifndef _Scorpion
#define _Scorpion

#include "TEAL\CommonElements.h"

//Note: Forward declare to avoid include - loop since Dart.h includes Scorpion.h
class Dart;
class ScorpionMover;
class ScorpionMoveBaseState;
//class ScorpionFactory;

#include "ScorpionFactory.h"

class Scorpion : public GameObject
{
public:

	Scorpion();
	Scorpion(Scorpion& copyScorpion) = delete;
	Scorpion& operator=(Scorpion&) = delete;
	~Scorpion() = default;

	void Initialize(sf::Vector2f p, ScorpionMover* _myMoverRef, ScorpionMoveBaseState* setDir);

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision(GameObject* go) {};

	//The dart will cause the Scorpion to lose 1 health, and the dart will then destroy itself
	virtual void Collision(Dart* other);

	//Set the row and column of the Scorpion
	void SetRowCol(int row, int col);

	//Get the row or the col of the Scorpion
	int GetMyRow();
	int GetMyCol();

	//Set the row of the Scorpion
	void SetMyRow(int newRow);
	void SetMyCol(int newCol);

	//Set the position of the Scorpion
	void SetMyPos(sf::Vector2f _newPos);

	//Get the position of the Scorpion
	sf::Vector2f GetMyPos();

	

	ScorpionMover* GetMyMover();

private:
	sf::Vector2f Pos;
	AnimatedSprite ScorpionSprite;
	CollisionTools::TextureBitmap* bitmap;

	ScorpionMoveBaseState* pCurrState;

	//The Scorpion will store it's grid position
	int ScorpionRow;
	int ScorpionCol;

	//Variables related to the initialization and animation of the sprite from a sprite sheet
	const int ScorpionFrameCountWidth = 4;		//Number of sprites that will be cycled through in each row
	const int ScorpionFrameCountHeight = 1;		//Number of sprites that will be cycled through in each column
	const float ScorpionSpriteFPS = 15.0f;		//Frame speed at which the sprites will be cycled through
	const int ScorpionSpriteFirstFrame = 0;		//For setting the animation of the sprite given the different sprites in the sheet
	const int ScorpionSpriteLastFrame = 3;		//For setting the animation of the sprite given the different sprites in the sheet
	const float spriteOriginSizeDivisor = 2.0f;		//Determines where the (0,0) position of the sprite will be given the size of the texture rectangle
	const float spriteFlipByScale = 1.0f;		//Flip the scorpion sprite

	//To tell if the given object has a flipped sprite
	bool flippedSprite;

	//Reference to the Scorpion mover that will handle movement for the Scorpion
	ScorpionMover* myMoverRef;

	//Scorpion game properties
	static const int ScorpionSpawnHealth = 2;

	//For counting the pixels traveled by the Scorpion to know it's grid pos
	int countMovement;
};

#endif