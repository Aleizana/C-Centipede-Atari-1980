#include "HUDGameOver.h"
#include "FontString.h"
#include "AwesomeFont.h"
#include "PlayerManager.h"
#include "Player.h"
#include "GameManager.h"
#include "TEAL/CommonElements.h"
#include "HighscoreManager.h"
#include "GridManager.h"

HUDGameOver::HUDGameOver()
{
	myFont = new AwesomeFont;

	sf::Vector2f player1DisplayPos = sf::Vector2f((float)GameManager::GetGridMgr()->GetPixelDistance() * plr1PosOffset_X, 0.0f);

	//Create a display for player 1 (AI in this case) with 0 lives and 0 score
	storedDisplays.push_back(new FontString(player1DisplayPos, myFont, GameManager::GetPlayerMgr()->GetPlayerByEnum(GameManager::GetPlayerMgr()->PlayerNumber::Player_1)->GetPlayerScore(), 
		GameManager::GetPlayerMgr()->GetPlayerByEnum(GameManager::GetPlayerMgr()->PlayerNumber::Player_1)->GetPlayerLives()));

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

	CreateGameOverDisplay();
}

void HUDGameOver::Draw()
{
	for (FontString* display : storedDisplays)
	{
		display->Draw();
	}

}

void HUDGameOver::Destroy()
{
	//Delete each of the stored font strings
	for (auto it = storedDisplays.begin(); it != storedDisplays.end(); ++it) {
		delete* it;
	}

	storedDisplays.clear();


	//Delete the font reference
	delete myFont;
}

void HUDGameOver::ChangeScoreDisplay(int newScore)
{
	//do nothing
}

void HUDGameOver::ChangeLivesDisplay(int newLives)
{
	//do nothing
}

sf::Vector2f HUDGameOver::GetBottomOfDisplayPos()
{
	return enterInitialsDisplayPos;
}

AwesomeFont* HUDGameOver::GetFont() const
{
	return myFont;
}

void HUDGameOver::CreateGameOverDisplay()
{
	float windowMiddleDiv = WindowManager::Window().getSize().x / middleOfScreenDivisor;

	float displayPosHeader_X = windowMiddleDiv - (((oneCoinOnePlayText.length() + oddToEvenLenSwitch) / middleOfScreenDivisor) * GameManager::GetGridMgr()->GetPixelDistance());

	sf::Vector2f gameOverDisplayPos = sf::Vector2f(displayPosHeader_X, (float)(gameOverTextOffsetFromHeader_Y * GameManager::GetGridMgr()->GetPixelDistance()));

	storedDisplays.push_back(new FontString(gameOverDisplayPos, myFont, oneCoinOnePlayText));

	int offsetCount = 0;

	std::string scoreAsSubString;

	offsetCount += textSectionOffset;

	displayPosHeader_X = windowMiddleDiv - ((gameOverText.length() + oddToEvenLenSwitch) / middleOfScreenDivisor) * GameManager::GetGridMgr()->GetPixelDistance();

	gameOverDisplayPos = sf::Vector2f(displayPosHeader_X, (float)((gameOverTextOffsetFromHeader_Y + offsetCount) * GameManager::GetGridMgr()->GetPixelDistance()));

	storedDisplays.push_back(new FontString(gameOverDisplayPos, myFont, gameOverText));

	offsetCount += textSectionOffset;

	displayPosHeader_X = windowMiddleDiv - ((newHighScoreText.length() + oddToEvenLenSwitch) / middleOfScreenDivisor) * GameManager::GetGridMgr()->GetPixelDistance();

	gameOverDisplayPos = sf::Vector2f(displayPosHeader_X, (float)((gameOverTextOffsetFromHeader_Y + offsetCount) * GameManager::GetGridMgr()->GetPixelDistance()));

	storedDisplays.push_back(new FontString(gameOverDisplayPos, myFont, newHighScoreText));

	offsetCount += nextLineOffset;

	displayPosHeader_X = windowMiddleDiv - ((enterInitialsText.length() + oddToEvenLenSwitch) / middleOfScreenDivisor) * GameManager::GetGridMgr()->GetPixelDistance();

	gameOverDisplayPos = sf::Vector2f(displayPosHeader_X, (float)((gameOverTextOffsetFromHeader_Y + offsetCount) * GameManager::GetGridMgr()->GetPixelDistance()));

	storedDisplays.push_back(new FontString(gameOverDisplayPos, myFont, enterInitialsText));

	offsetCount += textSectionOffset;

	gameOverDisplayPos = sf::Vector2f(windowMiddleDiv - (initialsLen * GameManager::GetGridMgr()->GetPixelDistance()), (float)((gameOverTextOffsetFromHeader_Y + offsetCount) * GameManager::GetGridMgr()->GetPixelDistance()));

	enterInitialsDisplayPos = gameOverDisplayPos;
}
