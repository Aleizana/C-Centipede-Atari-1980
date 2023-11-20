// Glyph
// Andre Berthiaume, May 2013

#ifndef _Glyph
#define _Glyph

#include "SFML\Graphics.hpp"
#include "TEAL/CommonElements.h"

class FontSheet; // forward declaration
class Dart;

class Glyph : public GameObject
{
private:
	FontSheet* fntSheet;
	int cellIndex;
	sf::Vector2f position;

	virtual void Destroy();

	sf::Sprite GlyphSprite;
	CollisionTools::TextureBitmap bitmap;

	const int spriteRectWidth = 16;
	const int spriteRectHeight = 16;
	const int spriteRectInitLeft = 0;
	const int spriteRectInitTop = 0;

	//Sprite rect used to take the single mushroom sprite from the sprite sheet
	sf::IntRect spriteRect;



public:
	Glyph();
	Glyph(Glyph& copyGlyph) = delete;
	Glyph& operator=(Glyph&) = delete;
	~Glyph() = default;

	Glyph(FontSheet* sheet, int cellInd, sf::Vector2f pos);
	void InitGlyph(FontSheet* sheet, int cellInd, sf::Vector2f pos);
	void Draw();

	virtual void Collision(GameObject* go) {};

	//The dart will cause the mushroom to lose 1 health, and the dart will then destroy itself
	virtual void Collision(Dart* other);

};


#endif _Glyph