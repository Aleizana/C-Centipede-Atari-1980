#ifndef _HighscoreManager
#define _HighscoreManager

#include <vector>

class HighscoreManager
{
private:
	
	std::vector<std::pair<int, std::string>> highscoreList;

	//Maximum length of the highscore list
	const int highscoreListLen = 8;


public:
	HighscoreManager();
	HighscoreManager(const HighscoreManager&) = delete;
	HighscoreManager& operator=(const HighscoreManager&) = delete;
	~HighscoreManager() = default;

	bool CheckForNewHighScore(int newScore);

	void SetNewHighScore(int newScore, std::string plrInitials);

	//Returns the first/highest high score in the list
	int GetHighestScore();

	const std::vector<std::pair<int, std::string>> GetHighscoreList() const;
};

#endif