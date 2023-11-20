// FontSheet
// Andre Berthiaume, May 2013

#include "FontSheet.h"
#include "TEAL\WindowManager.h" 
#include "GlyphFactory.h"
#include "Glyph.h"

FontSheet::FontSheet(sf::Texture& tex, int CellCountHor, int CellCountVert)
{
	Fontexture = tex;

	// Rectangle dimension corresponding to a single cell of the sprite sheet
	cellWidth = tex.getSize().x / CellCountHor;
	cellHeight = tex.getSize().y / CellCountVert;

	GlyphCollection.resize(CellCountHor * CellCountVert);

	// Initialize each sprite with the corrrect rectangle
	int left;
	int top;
	for (int j = 0; j < CellCountVert; j++)
	{
		top = j * cellHeight;
		for (int i = 0; i < CellCountHor; i++)
		{
			left = i * cellWidth;
			GlyphCollection[j * CellCountHor + i] = sf::Sprite(Fontexture, sf::IntRect(left, top, cellWidth, cellHeight));
		}
	}
}

int FontSheet::CellWidth() {
	return cellWidth;
}

int FontSheet::CellHeight() {
	return cellHeight;
}

Glyph* FontSheet::GetGlyph(char c, sf::Vector2f pos)
{
	return GlyphFactory::CreateGlyph(this, CharToIndex(c), pos);	// as an extra efficiency, we should add a glyph recycling factory to use here
}

void FontSheet::Draw(int i, sf::Vector2f pos)
{
	sf::Sprite& OneGlyph = GlyphCollection[i];
	OneGlyph.setPosition(pos);
	WindowManager::Window().draw(OneGlyph);
}