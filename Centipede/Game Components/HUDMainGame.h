#ifndef _HUDMainGame
#define _HUDMainGame

#include "TEAL/CommonElements.h"
#include <vector>
#include "HUDManager.h"

class FontString;
class AwesomeFont;

class HUDMainGame : public HUDManager
{
public:
	HUDMainGame();
	HUDMainGame(HUDMainGame& copyMgr) = delete;
	HUDMainGame& operator=(HUDMainGame&) = delete;
	~HUDMainGame() = default;

	virtual void Draw() override;
	virtual void Destroy() override;

	virtual void ChangeScoreDisplay(int newScore) override;
	virtual void ChangeLivesDisplay(int newLives) override;

	virtual AwesomeFont* GetFont() const override;

private:
	const enum DisplayIndices { Player1_Display, High_Score, Player2_Display};

	AwesomeFont* myFont;

	std::vector<FontString*> storedDisplays;

	const int plr2PosOffset_X = 23;

	const std::string nullHighScoreText = "0000000";
};


#endif _HUDMainGame