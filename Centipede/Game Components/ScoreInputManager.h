// ScoreInputManager
// Andre Berthiaume, May 2013

#ifndef _ScoreInputManager
#define _ScoreInputManager

#include "TEAL/CommonElements.h"
#include <list>
#include <vector>

class AwesomeFont;
class HighscoreManager;
class Glyph;

class ScoreInputManager : public GameObject
{
public:
	ScoreInputManager() = default;
	ScoreInputManager(ScoreInputManager& copyScoreInputManager) = delete;
	ScoreInputManager& operator=(ScoreInputManager&) = delete;
	~ScoreInputManager() = default;

	ScoreInputManager(AwesomeFont* newFont, sf::Vector2f bottomOfHUD);
	virtual void TextEntered(sf::Uint32 UnicodeValue);
	virtual void Draw();
	virtual void Destroy();

private:
	AwesomeFont* myFont;	

	std::list<Glyph*> symbols;
	sf::Vector2f nextpos;

	std::vector<std::string> initialsListAsString;

	const std::string initialInputChar = "A";

	const int maxNumInitials = 3;

	const sf::Uint32 enterVal = 13;
	const sf::Uint32 backspaceVal = 8;

	//Prevents the backspace input from clearing all of the glyphs from the list, as one is needed to represent the one the player is selecting
	const int BackspaceSizeLimit = 1;

	int holdScore;

	
};


#endif _ScoreInputManager