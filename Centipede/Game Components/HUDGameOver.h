#ifndef _HUDGameOver
#define _HUDGameOver

#include "TEAL/CommonElements.h"
#include <vector>
#include "HUDManager.h"

class FontString;
class AwesomeFont;


class HUDGameOver : public HUDManager
{
public:
	HUDGameOver();
	HUDGameOver(HUDGameOver& copyMgr) = delete;
	HUDGameOver& operator=(HUDGameOver&) = delete;
	~HUDGameOver() = default;

	virtual void Draw() override;
	virtual void Destroy() override;

	virtual void ChangeScoreDisplay(int newScore) override;
	virtual void ChangeLivesDisplay(int newLives) override;

	sf::Vector2f GetBottomOfDisplayPos();

	virtual AwesomeFont* GetFont() const override;

private:
	const enum DisplayIndices { Player1_Display, High_Score, Player2_Display, Game_Over_Text};

	void CreateGameOverDisplay();

	const int gameOverTextOffsetFromHeader_Y = 12;

	const int textSectionOffset = 2;

	//Used to add to the "odd" (math) length of a string so that it can be divided by 2 for positioning purposes
	const int oddToEvenLenSwitch = 1;

	const int nextLineOffset = 1;

	const int initialsLen = 3;

	const std::string oneCoinOnePlayText = "1 COIN 1 PLAY";

	const std::string gameOverText = "GAME OVER";

	const std::string newHighScoreText = "GREAT SCORE";

	const std::string enterInitialsText = "ENTER YOUR INITIALS";

	sf::Vector2f enterInitialsDisplayPos;
};


#endif _HUDGameOver