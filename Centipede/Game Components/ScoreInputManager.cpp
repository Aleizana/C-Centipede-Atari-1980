#include "ScoreInputManager.h"
#include "GridManager.h"
#include "AwesomeFont.h"
#include "Glyph.h"
#include "HighscoreManager.h"
#include "GameManager.h"
#include "PlayerManager.h"
#include "Player.h"
#include "GlyphFactory.h"
#include "PlayMode.h"

ScoreInputManager::ScoreInputManager(AwesomeFont* newFont, sf::Vector2f bottomOfHUD)
{
	RegisterInput(InputFlags::TextEntered);

	myFont = newFont;
	
	nextpos = bottomOfHUD;

	//Set the letter "A" as the first letter shown in the initial input
	symbols.push_back(myFont->GetGlyph(initialInputChar.at(0), nextpos));

	//Add the initial character to the vector of strings
	initialsListAsString.push_back(initialInputChar);
}

void ScoreInputManager::TextEntered(sf::Uint32 UnicodeValue)
{
	if (UnicodeValue == enterVal)
	{
		//If the user does not have 3 initials entered, show the default value for the next initial
		if (symbols.size() < (size_t)maxNumInitials)
		{
			//Move the user to enter the next initial
			nextpos.x += GameManager::GetGridMgr()->GetPixelDistance();

			//Add the default initial "A" to the initial list
			symbols.push_back(myFont->GetGlyph(initialInputChar.at(0), nextpos));

			//Add the initial character to the vector of strings
			initialsListAsString.push_back(initialInputChar);
		}
		//If all of the initials are entered, send the initials to the highscore manager and mark this instance for deletion
		else
		{
			//Build the string of the initials from the vector of strings
			std::string holdString = "";

			for (size_t i = 0; i < initialsListAsString.size(); i++)
			{
				holdString += initialsListAsString.at(i);
			}

			//Send the new data to the highscore manager for updating
			GameManager::GetHighscoreManager()->SetNewHighScore(GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerScore(), holdString);

			for (Glyph* item : symbols)
			{
				item->MarkForDestroy();
			}

			//Tell the player manager to handle the game over now that the initials have been entered
			GameManager::GetPlayMode()->HandleGameOver();
		}
		
	}
	else if (UnicodeValue == backspaceVal)
	{
		if (symbols.size() != BackspaceSizeLimit)
		{
			Glyph* holdPoppedGlyph = symbols.back();

			holdPoppedGlyph->MarkForDestroy();

			//Remove the current, unaccepted initial
			symbols.pop_back();

			//Remove the current, unaccepted initial from the string vector
			initialsListAsString.pop_back();

			//Update the pos of the initial currently being entered
			nextpos.x -= GameManager::GetGridMgr()->GetPixelDistance();
		}
	}
	else if ((((char&)UnicodeValue >= (int)'a' && (char&)UnicodeValue <= (int)'z')) || ((char&)UnicodeValue >= (int)'A' && (char&)UnicodeValue <= (int)'Z') || (char&)UnicodeValue == ' ')
	{
		Glyph* holdPoppedGlyph = symbols.back();

		holdPoppedGlyph->MarkForDestroy();

		//Remove the previous temporary initial at that pos
		symbols.pop_back();

		//Remove the previous temporary initial at that pos from the string vector
		initialsListAsString.pop_back();

		//Update the initial with the user-selected one
		symbols.push_back(myFont->GetGlyph((char)UnicodeValue, nextpos));

		//Add the character to the vector of strings
		initialsListAsString.push_back(Tools::ToString((char)UnicodeValue));
	}
	
	
}

void ScoreInputManager::Draw()
{
	for (Glyph* charRef : symbols)
	{
		charRef->Draw();
	}
}

void ScoreInputManager::Destroy()
{
	for (Glyph* item : symbols)
	{
		item->MarkForDestroy();
	}
}


