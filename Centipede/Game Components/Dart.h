#ifndef _Dart
#define _Dart

#include "TEAL\CommonElements.h"
#include "Blaster.h"

//Note: Forward declares to avoid include - loop since Mushroom.h, Flea.h include Dart.h
class Mushroom;
class Flea;
class CentipedeHead;
class CentipedeBody;
class Scorpion;
class Spider;
class Glyph;

class Dart : public GameObject
{
public:
	Dart();
	Dart& operator=(const Dart&) = delete;
	Dart(Dart& _copyDart) = delete;
	~Dart() = default;

	void Initialize(sf::Vector2f p);

	virtual void Draw();
	virtual void Update();
	virtual void Destroy();

	virtual void Collision(GameObject* other) {};

	//When colliding with a mushroom, both the dart will destroy itself and the mushroom will lose 1 point of health
	void Collision(Mushroom* other);

	//When colliding with a flea, both the dart will destroy itself and the flea will lose 1 point of health
	void Collision(Flea* other);

	//When colliding with a scorpion, both the dart will destroy itself and the scorpion will lose 1 point of health
	void Collision(Scorpion* other);

	//When colliding with a centipedehead, both the dart will destroy itself and the centipede head will lose 1 point of health
	//Mark for destroy on the DART is done by the centipede head to avoid anything else taking damage such as the spawned mushroom
	void Collision(CentipedeHead* other);

	//When colliding with a centipedebody, both the dart will destroy itself and the centipede body will lose 1 point of health
	//Mark for destroy on the DART is done by the centipede head to avoid anything else taking damage such as the spawned mushroom
	void Collision(CentipedeBody* other);

	//When colliding with a spider, both the dart and the spider will be destroyed
	void Collision(Spider* other);

	//When colliding with a glyph, destroy the dart
	void Collision(Glyph* other);

private:
	//Speed of the dart
	const int dartSpeedConst = 15;

	//Y-pos on the screen that signifies when the dart needs to be destroyed
	const int dartYThreshold = 0;

	sf::Vector2f Pos;
	sf::Sprite DartSprite;
	CollisionTools::TextureBitmap bitmap;
};

#endif 