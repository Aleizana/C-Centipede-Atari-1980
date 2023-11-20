#ifndef _HUDManager
#define _HUDManager

#include "TEAL/CommonElements.h"
#include <vector>

class FontString;
class AwesomeFont;

class HUDManager : public GameObject
{
public:
	HUDManager() = default;
	HUDManager(HUDManager& copyMgr) = delete;
	HUDManager& operator=(HUDManager&) = delete;
	~HUDManager() = default;

	virtual void Draw() = 0;
	virtual void Destroy() = 0;

	virtual void ChangeScoreDisplay(int newScore) = 0;
	virtual void ChangeLivesDisplay(int newLives) = 0;

	virtual AwesomeFont* GetFont() const = 0;

protected:
	AwesomeFont* myFont;

	std::vector<FontString*> storedDisplays;

	const int plr1PosOffset_X = 3;

	const float middleOfScreenDivisor = 2.0f;

	const std::string nullHighScoreText = "000000";

private:
	
};


#endif _HUDManager