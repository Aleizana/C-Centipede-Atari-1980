#ifndef _MushroomReg
#define _MushroomReg

#include "TEAL\CommonElements.h"

//Note: Forward declare to avoid include - loop since Dart.h and MushroomSpawner.h include Mushroom.h
class Dart;
class Spider;
class Scorpion;
class MushroomState;

class Mushroom : public GameObject
{
public:
	Mushroom();
	Mushroom(Mushroom& copyMushroom) = delete;
	Mushroom& operator=(Mushroom&) = delete;
	~Mushroom() = default;

	void Initialize(sf::Vector2f p);

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision(GameObject* go) {};

	//The dart will cause the mushroom to lose 1 health, and the dart will then destroy itself
	virtual void Collision(Dart* other);

	//The spider will cause the mushroom to be destroyed on contact
	virtual void Collision(Spider* other);

	//The mushroom spawner will set the row and column of the mushroom
	void SetRowCol(int row, int col);

	void ActivatePoisonState();
	
	//Probably unneeded
	virtual void ResetHealth() override;

	virtual const int GetMyRow() const override;
	virtual const int GetMyCol() const override;

	void ResetState();

	sf::Vector2f GetPos();

	sf::Sprite GetSprite();

	virtual const int GetStartingHP() const override;

private:
	sf::Vector2f Pos;
	sf::Sprite MainSprite;
	CollisionTools::TextureBitmap* bitmap;

	//The mushroom will store it's grid position
	int myRow;
	int myCol;

	//Constants for mushroom game properties
	//Max amount of damage the mushroom can take
	const int MushHealth = 4;

	//Determines where the (0,0) position of the sprite will be given the size of the texture rectangle
	const float spriteOriginSizeDivisor = 2.0f;

	const MushroomState* pCurrState;

	//Stores the amount of damage taken so that the sprite can reflect it in its appearance
	//int dmgTaken;

	//Sprite rect used to take the single mushroom sprite from the sprite sheet
	//sf::IntRect spriteRect;

	//int poisonedSpriteSheetOffset;

};

#endif