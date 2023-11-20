// FontSheet
// Andre Berthiaume, May 2013

#ifndef _FontSheet
#define _FontSheet

#include "SFML\Graphics.hpp"
#include "Glyph.h"
#include <vector>

class FontSheet
{
public:
	FontSheet() = delete;
	FontSheet(const FontSheet&) = delete;
	FontSheet& operator=(const FontSheet&) = delete;
	virtual ~FontSheet() = default;

	FontSheet(sf::Texture& tex, int CellCountHor, int CellCountVert);
	int CellWidth();
	int CellHeight();
	void Draw(int i, sf::Vector2f pos);

	Glyph* GetGlyph(char c, sf::Vector2f pos);

private:
	std::vector<sf::Sprite> GlyphCollection;
	sf::Texture Fontexture;
	int cellWidth;
	int cellHeight;

	virtual int CharToIndex(char& c) = 0;  // abstract method. 
};


#endif _FontSheet