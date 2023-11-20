#ifndef _WaveMgr
#define _WaveMgr

#include <vector>

//Forward declarations to avoid include loop with Wave.h
class Wave;



class WaveManager
{
public:
	WaveManager() = default;
	WaveManager& operator= (const WaveManager&) = delete;
	WaveManager(const WaveManager& copyWave) = delete;
	~WaveManager();

	//For creating the wave manager with a file to read from
	WaveManager(const char* const pFileName);

	Wave* GetWaveByNumber(int waveNum);

	int GetMaxWaves();

	//Convert the string pulled from the wave file into game data
	void HandleStringToWave(std::string readString, int lineNum, int& lineCounter);

private:
	//For storing each of the waves that will be playable in the game
	std::vector<Wave*> waveList;

	//Stored from the wave file to know the limit on how many waves there are
	int maxWaves;

	//The number of lines that must be read before a new wave is created
	const int linesBeforeNewWave = 17;

	//The base level for the line count check
	const int firstLineCountCheck = 0;

	const float speedCantEqualZeroCheck = 0.0f;
};

#endif
