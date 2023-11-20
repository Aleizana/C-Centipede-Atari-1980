#ifndef _Blast
#define _Blast

#include "TEAL\CommonElements.h"

//#include "MainGameScene.h"

//Forward declarations to avoid include loop
class Dart;
class Flea;
class BlasterSpawner;
class Mushroom;
class ControllerBase;
class CentipedeHead;
class Spider;
class CentipedeBody;

class Blaster : public GameObject
{
public:
	Blaster();
	Blaster& operator=(const Blaster&) = delete;
	Blaster(Blaster& _copyBlaster) = delete;
	~Blaster() = default;

	void Initialize(sf::Vector2f p, ControllerBase* _ctrlMgrRef);

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey);

	virtual void Collision(GameObject* other) {};

	//Reverses the direction of the blaster when it attempts to pass through a mushroom
	void Collision(Mushroom* otherObj);

	//Kills the blaster and tells the factory to spawn another
	void Collision(Flea* otherObj);

	//Kills the blaster and tells the factory to spawn another
	void Collision(CentipedeHead* other);

	//Kills the blaster and tells the factory to spawn another
	void Collision(CentipedeBody* other);

	//Kills the blaster and tells the factory to spawn another
	void Collision(Spider* other);

	//For any controllers to reference the blaster and move them based upon a 2fVector
	void MoveBlaster(sf::Vector2f _inputOffset);

	//For the controller manager to reset the impulse of the blaster
	void SetImpulse(float x_val, float y_val);

	//Returns the position of the blaster
	sf::Vector2f GetPos();

	void SetPos(sf::Vector2f newPos);
	
private:
	//The amount of time the system sleeps when the player dies
	const int plrDeathTimer = 1000;

	//The draw order priority of the blaster sprite
	const int blasterDrawOrder = 1000;

	//Offset applied by player input
	float inputOffset;

	//The y-limit through which the blaster can move
	float playerAreaLimit = 368.0f;

	const float ExplosionScalar = 2.0f;

	//Total movement value
	sf::Vector2f impulse;

	//Position of the blaster
	sf::Vector2f Pos;

	//Sprite attached to the blaster
	sf::Sprite BlasterSprite;

	//Collision map
	CollisionTools::TextureBitmap bitmap;

	//Reference to the player controller so that the blaster can have it's movement handled by the correct inputs
	ControllerBase* plrCtrlRef;
};

#endif _Blast