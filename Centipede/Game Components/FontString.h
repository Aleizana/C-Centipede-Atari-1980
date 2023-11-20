#ifndef _FontString
#define _FontString

#include "SFML\Graphics.hpp"

class Glyph;
class AwesomeFont;

class FontString
{
private:
	sf::Vector2f displayPosStart;
	std::vector<Glyph*> displayList;

	AwesomeFont* myFont;

	//The number of blaster sprites displayed for the player lives will be their lives - 1
	const int livesDisplayOffset = 1;

	const int plrScoreTextLenOffset = 4;

	void PassGlyphToGrid(sf::Vector2f glyphPos, Glyph* glyphToPassToGrid);

public:
	FontString() = default;
	FontString(FontString& copyFontString) = delete;
	FontString& operator=(FontString&) = delete;
	~FontString();
	FontString(sf::Vector2f newPos, AwesomeFont* fontRef, int score, int lives = 0, bool flipScoreLives = false);
	FontString(sf::Vector2f newPos, AwesomeFont* fontRef, std::string);
	FontString(sf::Vector2f newPos, AwesomeFont* fontRef, int score, std::string initials);

	void Draw();

	void UpdateDisplay(int score = 0, int lives = 0, bool flipScoreLives = false);
	void UpdateDisplay(std::string stringToGlyph);
	void UpdateDisplayHighscoreList(int score, std::string initials);
};


#endif _FontString