#include "HUDMainGame.h"
#include "FontString.h"
#include "AwesomeFont.h"
#include "PlayerManager.h"
#include "Player.h"
#include "GameManager.h"
#include "TEAL/CommonElements.h"
#include "HighscoreManager.h"
#include "GridManager.h"

HUDMainGame::HUDMainGame()
{
	myFont = new AwesomeFont;

	sf::Vector2f player1DisplayPos = sf::Vector2f((float)GameManager::GetGridMgr()->GetPixelDistance() * plr1PosOffset_X, 0.0f);

	storedDisplays.push_back(new FontString(player1DisplayPos, myFont, GameManager::GetPlayerMgr()->GetPlayerByEnum(GameManager::GetPlayerMgr()->Player_1)->GetPlayerScore(),
		GameManager::GetPlayerMgr()->GetPlayerByEnum(GameManager::GetPlayerMgr()->Player_1)->GetPlayerLives()));

	int holdHighScore = GameManager::GetHighscoreManager()->GetHighestScore();

	//If the high score is equal to zero, display the null high score text
	if (holdHighScore == 0)
	{
		sf::Vector2f highScoreDisplayPos = sf::Vector2f(
			(WindowManager::Window().getSize().x / middleOfScreenDivisor) - (GameManager::GetGridMgr()->GetPixelDistance() * nullHighScoreText.length() / middleOfScreenDivisor),
			0.0f);

		storedDisplays.push_back(new FontString(highScoreDisplayPos, myFont, nullHighScoreText));
	}
	else
	{
		//Convert the high score to a string
		std::string holdHighscoreString = Tools::ToString(holdHighScore);

		//Position the high score in the middle of the screen based off of it's length
		sf::Vector2f highScoreDisplayPos = sf::Vector2f(
			(WindowManager::Window().getSize().x / middleOfScreenDivisor) - (GameManager::GetGridMgr()->GetPixelDistance() * holdHighscoreString.length() / middleOfScreenDivisor),
			0.0f);

		//Add the new font string to the displays list
		storedDisplays.push_back(new FontString(highScoreDisplayPos, myFont, holdHighscoreString));
	}

	//Only display player 2's lives and score if the game is in 2 player mode
	if (GameManager::Get2PlayerModeBool())
	{
		sf::Vector2f player2DisplayPos = sf::Vector2f((float)myFont->CellWidth() * plr2PosOffset_X, 0.0f);

		storedDisplays.push_back(new FontString(player2DisplayPos, myFont, GameManager::GetPlayerMgr()->GetPlayerByEnum(GameManager::GetPlayerMgr()->Player_2)->GetPlayerScore(),
			GameManager::GetPlayerMgr()->GetPlayerByEnum(GameManager::GetPlayerMgr()->Player_2)->GetPlayerLives(), true));
	}

}

void HUDMainGame::Draw()
{
	for (FontString* display : storedDisplays)
	{
		display->Draw();
	}

}

void HUDMainGame::Destroy()
{
	//Delete each of the stored font strings
	for (auto it = storedDisplays.begin(); it != storedDisplays.end(); ++it) {
		delete* it;
	}
	storedDisplays.clear();

	//Delete the font reference
	delete myFont;
}

void HUDMainGame::ChangeScoreDisplay(int newScore)
{
	if (GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerNumber() == GameManager::GetPlayerMgr()->PlayerNumber::Player_1)
	{
		storedDisplays.at((size_t)DisplayIndices::Player1_Display)->UpdateDisplay(newScore, GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerLives());
	}
	else if (GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerNumber() == GameManager::GetPlayerMgr()->PlayerNumber::Player_2)
	{
		storedDisplays.at((size_t)DisplayIndices::Player2_Display)->UpdateDisplay(newScore, GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerLives(), true);
	}
	else    //High Score
	{
		storedDisplays.at((size_t)DisplayIndices::High_Score)->UpdateDisplay(newScore);
	}
}

void HUDMainGame::ChangeLivesDisplay(int newLives)
{
	if (GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerNumber() == GameManager::GetPlayerMgr()->PlayerNumber::Player_1)
	{
		storedDisplays.at((size_t)DisplayIndices::Player1_Display)->UpdateDisplay(GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerScore(), newLives);
	}
	else if (GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerNumber() == GameManager::GetPlayerMgr()->PlayerNumber::Player_2)
	{
		storedDisplays.at((size_t)DisplayIndices::Player2_Display)->UpdateDisplay(GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerScore(), newLives, true);
	}
}

AwesomeFont* HUDMainGame::GetFont() const
{
	return myFont;
}
