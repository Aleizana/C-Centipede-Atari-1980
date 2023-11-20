#include "FontString.h"
#include "TEAL\ResourceManager.h"
#include "TEAL\CommonElements.h"
#include <assert.h>
#include "Glyph.h"
#include "AwesomeFont.h"
#include "GlyphFactory.h"
#include "GridManager.h"
#include "PlayerManager.h"
#include "Player.h"
#include "Grid.h"
#include "GameManager.h"

void FontString::PassGlyphToGrid(sf::Vector2f glyphPos, Glyph* glyphToPassToGrid)
{
	//Divide the y-pos of the glyph by the cell size of the grid to get it's row
	int row = ((int)glyphPos.y / GameManager::GetGridMgr()->GetPixelDistance() + GameManager::GetGridMgr()->GetRowStartIndex());

	//Divide the x-pos of the glyph by the cell size of the grid to get it's col
	int col = (int)glyphPos.x / GameManager::GetGridMgr()->GetPixelDistance();

	//Pass the glyph to the grid so that it can occupy a space
	GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->PassGameObjectRef(row, col, (GameObject*)glyphToPassToGrid);
}

FontString::~FontString()
{
	for (Glyph* item : displayList)
	{
		item->MarkForDestroy();
	}
}

FontString::FontString(sf::Vector2f newPos, AwesomeFont* fontRef, int score, int lives, bool flipScoreLives)
{
	displayPosStart = newPos;

	myFont = fontRef;

	UpdateDisplay(score, lives, flipScoreLives);
}

FontString::FontString(sf::Vector2f newPos, AwesomeFont* fontRef, std::string stringToGlyph)
{
	displayPosStart = newPos;

	myFont = fontRef;

	UpdateDisplay(stringToGlyph);
}

FontString::FontString(sf::Vector2f newPos, AwesomeFont* fontRef, int score, std::string initials)
{
	displayPosStart = newPos;

	myFont = fontRef;

	UpdateDisplayHighscoreList(score, initials);
}

void FontString::Draw()
{
	for (size_t i = 0; i < displayList.size(); i++)
	{
		displayList.at(i)->Draw();
	}
		
}

void FontString::UpdateDisplay(int score, int lives, bool flipScoreLives)
{
	std::string holdText;

	if (score == 0)
	{
		holdText = Tools::ToString("00");
	}
	else
	{
		holdText = Tools::ToString(score);
	}

	if (lives != 0)
	{
		int holdLives = lives - livesDisplayOffset;

		for (int i = 0; i < holdLives; i++)
		{
			//Flip the placement of the lives and score for player 1 vs player 2
			if (!flipScoreLives)
			{
				holdText = Tools::ToString(holdText + "-");
			}
			else
			{
				holdText = Tools::ToString("-" + holdText);
			}
			
		}
	}

	for (Glyph* item : displayList)
	{
		item->MarkForDestroy();
	}

	displayList.clear();

	float holdX;

	//if (holdText.length() > (size_t)plrScoreTextLenOffset)
	//{
	//	//Align the score text one cell to the left based on it's length
	//	holdX = displayPosStart.x - (GameManager::GetGridMgr()->GetPixelDistance() * (holdText.length() - plrScoreTextLenOffset));
	//}
	//else
	//{
	//	holdX = displayPosStart.x;
	//}
	holdX = displayPosStart.x;
	

	sf::Vector2f displayPosIncrement = sf::Vector2f(holdX, 0.0f);

	Glyph* holdRef;

	for (size_t i = 0; i < holdText.length(); i++)
	{

		displayList.push_back(myFont->GetGlyph(holdText.at(i), displayPosIncrement));

		holdRef = displayList.back();

		//Get the glyph at the back at the list, which was just added, and pass it with its pos to the grid
		PassGlyphToGrid(displayPosIncrement, holdRef);

		// we must update the next position ourselves
		displayPosIncrement.x += GameManager::GetGridMgr()->GetPixelDistance();
	}
}

void FontString::UpdateDisplay(std::string stringToGlyph)
{
	for (Glyph* item : displayList)
	{
		item->MarkForDestroy();
	}

	displayList.clear();

	sf::Vector2f displayPosIncrement = displayPosStart;

	Glyph* holdRef;

	for (size_t i = 0; i < stringToGlyph.length(); i++)
	{
		displayList.push_back(myFont->GetGlyph(stringToGlyph.at(i), displayPosIncrement));

		holdRef = displayList.back();

		//Get the glyph at the back at the list, which was just added, and pass it with its pos to the grid
		PassGlyphToGrid(displayPosIncrement, holdRef);

		// we must update the next position ourselves
		displayPosIncrement.x += GameManager::GetGridMgr()->GetPixelDistance();
	}
}

void FontString::UpdateDisplayHighscoreList(int score, std::string initials)
{
	for (Glyph* item : displayList)
	{
		item->MarkForDestroy();
	}

	displayList.clear();

	sf::Vector2f displayPosIncrement = displayPosStart;

	Glyph* holdRef;

	std::string holdText;

	if (score == 0)
	{
		holdText = Tools::ToString("00 " + initials);
	}
	else
	{
		holdText = Tools::ToString(score) + " " + initials;
	}

	for (size_t i = 0; i < holdText.length(); i++)
	{
		displayList.push_back(myFont->GetGlyph(holdText.at(i), displayPosIncrement));

		holdRef = displayList.back();

		//Get the glyph at the back at the list, which was just added, and pass it with its pos to the grid
		PassGlyphToGrid(displayPosIncrement, holdRef);

		// we must update the next position ourselves
		displayPosIncrement.x += GameManager::GetGridMgr()->GetPixelDistance();
	}
}
