#include "HUDAttractor.h"
#include "FontString.h"
#include "AwesomeFont.h"
#include "PlayerManager.h"
#include "Player.h"
#include "GameManager.h"
#include "TEAL/CommonElements.h"
#include "HighscoreManager.h"
#include "GridManager.h"

HUDAttractor::HUDAttractor()
{
	myFont = new AwesomeFont;

	sf::Vector2f player1DisplayPos = sf::Vector2f((float)GameManager::GetGridMgr()->GetPixelDistance() * plr1PosOffset_X, 0.0f);

	//Create a display for player 1 (AI in this case) with 0 lives and 0 score
	storedDisplays.push_back(new FontString(player1DisplayPos, myFont, 0,0));

	int holdHighScore = GameManager::GetHighscoreManager()->GetHighestScore();

	float windowMiddleDiv = WindowManager::Window().getSize().x / middleOfScreenDivisor;

	

	//If the high score is equal to zero, display the null high score text
	if (holdHighScore == 0)
	{
		windowMiddleDiv -= (nullHighScoreText.length() / middleOfScreenDivisor) * GameManager::GetGridMgr()->GetPixelDistance();

		sf::Vector2f highScoreDisplayPos = sf::Vector2f(
			windowMiddleDiv,
			0.0f);

		storedDisplays.push_back(new FontString(highScoreDisplayPos, myFont, nullHighScoreText));
	}
	else
	{
		//Convert the high score to a string
		std::string holdHighscoreString = Tools::ToString(holdHighScore);

		windowMiddleDiv -= (holdHighscoreString.length() / middleOfScreenDivisor) * GameManager::GetGridMgr()->GetPixelDistance();

		//Position the high score in the middle of the screen based off of it's length
		sf::Vector2f highScoreDisplayPos = sf::Vector2f(
			windowMiddleDiv,
			0.0f);

		//Add the new font string to the displays list
		storedDisplays.push_back(new FontString(highScoreDisplayPos, myFont, holdHighscoreString));
	}

	CreateHighscoreListDisplay();
}

void HUDAttractor::Draw()
{
	for (FontString* display : storedDisplays)
	{
		display->Draw();
	}

}

void HUDAttractor::Destroy()
{
	//Delete each of the stored font strings
	for (auto it = storedDisplays.begin(); it != storedDisplays.end(); ++it) {
		delete* it;
	}

	storedDisplays.clear();


	//Delete the font reference
	delete myFont;
}

void HUDAttractor::ChangeScoreDisplay(int newScore)
{
	//do nothing
}

void HUDAttractor::ChangeLivesDisplay(int newLives)
{
	//do nothing
}

AwesomeFont* HUDAttractor::GetFont() const
{
	return myFont;
}

void HUDAttractor::CreateHighscoreListDisplay()
{
	const std::vector<std::pair<int, std::string>> holdScoreList = GameManager::GetHighscoreManager()->GetHighscoreList();

	float windowMiddleDiv = WindowManager::Window().getSize().x / middleOfScreenDivisor;

	float displayPosHeader_X = windowMiddleDiv - (((scoreListHeader.length() + oddToEvenLenSwitch) / middleOfScreenDivisor) * GameManager::GetGridMgr()->GetPixelDistance());

	sf::Vector2f highScoreDisplayPos = sf::Vector2f(displayPosHeader_X, (float)(scoreListOffset_Y * GameManager::GetGridMgr()->GetPixelDistance()));

	storedDisplays.push_back(new FontString(highScoreDisplayPos, myFont, scoreListHeader));

	int offsetCount = 0;

	std::string scoreAsString;

	float displayPosScoreListItems_X;

	for (std::pair<int, std::string> scoreList : holdScoreList)
	{
		offsetCount++;

		if (scoreList.first == 0)
		{
			scoreAsString = "00";
		}
		else
		{
			scoreAsString = Tools::ToString(scoreList.first);
		}

		displayPosScoreListItems_X = displayPosHeader_X + ((scoreItemsOffsetFromHeader_X - scoreAsString.length()) * GameManager::GetGridMgr()->GetPixelDistance());

		highScoreDisplayPos = sf::Vector2f(displayPosScoreListItems_X, (float)((scoreListOffset_Y + offsetCount) * GameManager::GetGridMgr()->GetPixelDistance()));

		storedDisplays.push_back(new FontString(highScoreDisplayPos, myFont, scoreList.first, scoreList.second));
		
	}

	offsetCount += offsetFromBottomOfScoreList;

	displayPosHeader_X = windowMiddleDiv - ((oneCoinOnePlayText.length() + oddToEvenLenSwitch) / middleOfScreenDivisor) * GameManager::GetGridMgr()->GetPixelDistance();

	highScoreDisplayPos = sf::Vector2f(displayPosHeader_X, (float)((scoreListOffset_Y + offsetCount) * GameManager::GetGridMgr()->GetPixelDistance()));

	storedDisplays.push_back(new FontString(highScoreDisplayPos, myFont, oneCoinOnePlayText));

	offsetCount += offsetFromBottomOfScoreList;

	displayPosHeader_X = windowMiddleDiv - ((bonusLifeText.length() + oddToEvenLenSwitch) / middleOfScreenDivisor) * GameManager::GetGridMgr()->GetPixelDistance();

	highScoreDisplayPos = sf::Vector2f(displayPosHeader_X, (float)((scoreListOffset_Y + offsetCount) * GameManager::GetGridMgr()->GetPixelDistance()));

	storedDisplays.push_back(new FontString(highScoreDisplayPos, myFont, bonusLifeText));


	displayPosHeader_X = windowMiddleDiv - ((copyrightText.length() + oddToEvenLenSwitch) / middleOfScreenDivisor) * GameManager::GetGridMgr()->GetPixelDistance();

	highScoreDisplayPos = sf::Vector2f(displayPosHeader_X, (float)(WindowManager::Window().getSize().y - GameManager::GetGridMgr()->GetPixelDistance()));

	storedDisplays.push_back(new FontString(highScoreDisplayPos, myFont, copyrightText));
}
