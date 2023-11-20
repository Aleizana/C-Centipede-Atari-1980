#ifndef _HUDAttractor
#define _HUDAttractor

#include "TEAL/CommonElements.h"
#include <vector>
#include "HUDManager.h"

class FontString;
class AwesomeFont;


class HUDAttractor : public HUDManager
{
public:
	HUDAttractor();
	HUDAttractor(HUDAttractor& copyMgr) = delete;
	HUDAttractor& operator=(HUDAttractor&) = delete;
	~HUDAttractor() = default;

	virtual void Draw() override;
	virtual void Destroy() override;

	virtual void ChangeScoreDisplay(int newScore) override;
	virtual void ChangeLivesDisplay(int newLives) override;

	virtual AwesomeFont* GetFont() const override;

	void CreateHighscoreListDisplay();

private:
	const enum DisplayIndices { Player1_Display, High_Score, High_Score_List_AI };

	const int scoreListOffset_Y = 2;

	const int offsetFromBottomOfScoreList = 2;

	const int scoreItemsOffsetFromHeader_X = 5;

	//Used to add to the "odd" (math) length of a string so that it can be divided by 2 for positioning purposes
	const int oddToEvenLenSwitch = 1;

	const std::string scoreListHeader = "HIGH SCORES";

	const std::string oneCoinOnePlayText = "1 COIN 1 PLAY";

	const std::string bonusLifeText = "BONUS EVERY 12000";

	const std::string copyrightText = "[1980 ATARI";
};


#endif _HUDAttractor