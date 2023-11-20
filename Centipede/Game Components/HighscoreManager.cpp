#include "HighscoreManager.h"
#include <fstream>
#include <string>
#include "TEAL/CommonElements.h"
#include <assert.h>
#include "GameManager.h"


HighscoreManager::HighscoreManager()
{
	//Assign default values to the list to start the game
	highscoreList.assign(highscoreListLen, std::pair<int, std::string>(0, "ABC"));
}

bool HighscoreManager::CheckForNewHighScore(int newScore)
{
	//decleration of vector iterator
	std::vector<std::pair<int, std::string>>::iterator iter = highscoreList.begin();

	int holdScore;

	std::pair<int, std::string> holdPair;

	//Iterate through the scores of the list to add the new high score
	for (iter; iter < highscoreList.end(); iter++)
	{
		holdPair = *iter;


		holdScore = holdPair.first;

		//If the new score is greater than or equal to a score, insert it at that scores pos, moving the rest down the list
		if (newScore >= holdScore)
		{


			return true;

			//Exit loop now that the score has been added
			break;
		}
		
	}

	return false;
}

void HighscoreManager::SetNewHighScore(int newScore, std::string plrInitials)
{
	//decleration of vector iterator
	std::vector<std::pair<int, std::string>>::iterator iter = highscoreList.begin();

	int holdScore;

	std::pair<int, std::string> holdPair;

	//Iterate through the scores of the list to add the new high score
	for (iter; iter < highscoreList.end(); iter++)
	{
		holdPair = *iter;

		holdScore = holdPair.first;

		//If the new score is greater than or equal to a score, insert it at that scores pos, moving the rest down the list
		if (newScore >= holdScore)
		{
			highscoreList.insert(iter, std::pair<int, std::string>(newScore, plrInitials));
			
			//Remove the last item of the list to make space for the new item
			highscoreList.pop_back();


			//Exit loop now that the score has been added
			break;
		}

	}

}

int HighscoreManager::GetHighestScore()
{


	//The front of the highscore list is the highest value
	return highscoreList.front().first;
}

const std::vector<std::pair<int, std::string>> HighscoreManager::GetHighscoreList() const
{
	return highscoreList;
}
