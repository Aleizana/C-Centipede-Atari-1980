// Glyph
// Andre Berthiaume, May 2013

#include "Glyph.h"
#include "FontSheet.h"
#include "TEAL\ResourceManager.h"
#include <assert.h>
#include "Dart.h"

Glyph::Glyph()
{
	fntSheet = nullptr;
	cellIndex = 0;
	position = sf::Vector2f(0, 0);
	myState = GameObject::LifeState::ALIVE;
	myType = GameObject::ObjectType::GLYPH;

	

	spriteRect = sf::IntRect(spriteRectInitLeft, spriteRectInitTop, spriteRectWidth, spriteRectHeight);

	bitmap = ResourceManager::GetTextureBitmap("Alphabet");
	GlyphSprite = sf::Sprite(ResourceManager::GetTexture("Alphabet"), spriteRect);

	

	RegisterCollision<Glyph>(*this);
}

Glyph::Glyph(FontSheet* sheet, int cellInd, sf::Vector2f pos)
{
	fntSheet = sheet;
	position = pos;
	cellIndex = cellInd;

	GlyphSprite.setPosition(pos);

	//Set the (0,0) position for the sprite
	//GlyphSprite.setOrigin((float)GlyphSprite.getTextureRect().width, (float)GlyphSprite.getTextureRect().height);

	SetCollider(GlyphSprite, bitmap);

	RegisterCollision<Glyph>(*this);
}

void Glyph::InitGlyph(FontSheet* sheet, int cellInd, sf::Vector2f pos)
{
	fntSheet = sheet;
	position = pos;
	cellIndex = cellInd;

	GlyphSprite.setPosition(pos);

	SetCollider(GlyphSprite, bitmap);

	RegisterCollision<Glyph>(*this);
}



void Glyph::Draw()
{
	assert(fntSheet != nullptr);

	fntSheet->Draw(cellIndex, position);
}

void Glyph::Collision(Dart* other)
{
	//Destroy the dart
	other->MarkForDestroy();
}

void Glyph::Destroy()
{
	ConsoleMsg::WriteLine("Deleted glyph!");
	DeregisterCollision<Glyph>(*this);

}