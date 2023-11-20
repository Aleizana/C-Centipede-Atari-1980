#include "WaveManager.h"
#include "Wave.h"

#include "../Game Components/TEAL/CommonElements.h"

#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

WaveManager::WaveManager(const char* const pFileName)
{
	//To store the handle for the file that will be read
	std::ifstream pFileHandle;

	//Assert that the filename is valid
	assert(pFileName);

	//Open the text file
	pFileHandle.open(pFileName, std::ios::in);

	//Assert that the file was correctly opened
	assert(pFileHandle.is_open() == true && "File couldn't open");

	//Set the max number of waves to 0 at the start
	maxWaves = 0;

	//Holds the text from a line of the file
	std::string holdText;

	int lineNum = firstLineCountCheck;

	int lineCounter = firstLineCountCheck;

	while (pFileHandle.peek() != EOF)
	{
		//Get the string representing data
		std::getline(pFileHandle, holdText);

		lineNum++;

		//Line counter is incremented in the handle string so as to avoid conflicts between resetting the counter and incrementing it
		HandleStringToWave(holdText, lineNum, lineCounter);

	}

	//Check to make sure the last wave was completely filled out
	if (lineCounter != linesBeforeNewWave)
	{
		ConsoleMsg::ShowError("At file line number " + Tools::ToString(lineNum) + " did not complete the final wave. Each wave must have " + Tools::ToString(linesBeforeNewWave) + 
			" parameters. This one had: " + Tools::ToString(lineCounter));
	}

	//Close the file stream
	pFileHandle.close();
}

Wave* WaveManager::GetWaveByNumber(int waveNum)
{
	return waveList.at(waveNum - 1);
}

int WaveManager::GetMaxWaves()
{
	return maxWaves;
}

void WaveManager::HandleStringToWave(std::string readString, int lineNum, int& lineCounter)
{
	std::string stringSub;

	std::string subSecondHalf;

	if (readString.find(":") == std::string::npos)
	{
		ConsoleMsg::ShowError("At file line number " + Tools::ToString(lineNum) + " expected a ':' but did not find one. Instead found: '" + readString + "'");
	}

	size_t holdKeySeparator = readString.find(":");

	stringSub = readString.substr(0, holdKeySeparator);

	Wave* waveRef;

	//Get the value half of the string after the colon and convert it into an integer
	subSecondHalf = readString.substr(holdKeySeparator + 1, std::string::npos);
	int valueSecondHalf = std::stoi(subSecondHalf);

	if (stringSub.compare("Wave") == 0)
	{
		if (lineCounter == firstLineCountCheck || lineCounter == linesBeforeNewWave)
		{
			//Add a new wave to the wave list
			waveList.push_back(new Wave);

			maxWaves++;

			lineCounter = 0;
		}
		else
		{
			ConsoleMsg::ShowError("At file line number " + Tools::ToString(lineNum) + " got a new wave declaration but did not complete the previous one. Each wave must have " +
				Tools::ToString(linesBeforeNewWave) + " parameters. This one had: " + Tools::ToString(lineCounter));
			
		}
		
	}
	else if (stringSub.compare("Centipede Length") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back(); 
		waveRef->SetCentiLenWave(valueSecondHalf);

		lineCounter++;
	}
	else if (stringSub.compare("Centipede Speed") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back();

		if ((float)valueSecondHalf == speedCantEqualZeroCheck)
		{
			ConsoleMsg::ShowError("At file line number " + Tools::ToString(lineNum) + " got 0 for Centipede Speed. Ensure speed is a value greater than zero");
		}
		else
		{
			waveRef->SetCentiSpeedWave((float)valueSecondHalf);

			lineCounter++;
		}

		
	}
	else if (stringSub.compare("Centipede Solo Heads Count") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back();
		waveRef->SetCentiSingleHeadSpawnWave(valueSecondHalf);

		lineCounter++;
	}
	else if (stringSub.compare("Centipede Solo Heads Speed") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back();

		if ((float)valueSecondHalf == speedCantEqualZeroCheck)
		{
			ConsoleMsg::ShowError("At file line number " + Tools::ToString(lineNum) + " got 0 for Centipede Solo Head Speed. Ensure speed is a value greater than zero");
		}
		else
		{
			waveRef->SetSoloHeadSpeed((float)valueSecondHalf);

			lineCounter++;
		}
		
	}
	else if (stringSub.compare("Centipede Solo Heads Player Area Speed") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back();

		if ((float)valueSecondHalf == speedCantEqualZeroCheck)
		{
			ConsoleMsg::ShowError("At file line number " + Tools::ToString(lineNum) + " got 0 for Centipede Solo Heads Player Area Speed. Ensure speed is a value greater than zero");
		}
		else
		{
			waveRef->SetSoloHeadPlrAreaSpeed((float)valueSecondHalf);

			lineCounter++;
		}
		

		
	}
	else if (stringSub.compare("Centipede Solo Heads Player Area Spawn") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back();

		if (valueSecondHalf == 0)
		{
			waveRef->SetSingleHeadPresentInPlrArea(false);
		}
		else if (valueSecondHalf == 1)
		{
			waveRef->SetSingleHeadPresentInPlrArea(true);
		}
		else
		{
			ConsoleMsg::ShowError("At file line number " + Tools::ToString(lineNum) + "Centipede Solo Heads Player Area Spawn needs to be either 0 for false or 1 for true.");
		}

		lineCounter++;
	}
	else if (stringSub.compare("Centipede Solo Heads Player Area Spawn Count") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back();
		waveRef->SetSingleHeadSpawnInPlrAreaCount(valueSecondHalf);

		lineCounter++;
	}
	else if (stringSub.compare("Centipede Solo Heads Present") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back();

		if (valueSecondHalf == 0)
		{
			waveRef->SetSingleHeadPresent(false);
		}
		else if (valueSecondHalf == 1)
		{
			waveRef->SetSingleHeadPresent(true);
		}
		else
		{
			ConsoleMsg::ShowError("At file line number " + Tools::ToString(lineNum) + "Centipede Solo Heads Present needs to be either 0 for false or 1 for true.");
		}

		lineCounter++;
	}
	else if (stringSub.compare("Spider Present") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back();

		if (valueSecondHalf == 0)
		{
			waveRef->SetSpiderPresentWave(false);
		}
		else if (valueSecondHalf == 1)
		{
			waveRef->SetSpiderPresentWave(true);
		}
		else
		{
			ConsoleMsg::ShowError("At file line number " + Tools::ToString(lineNum) + "Spider Present needs to be either 0 for false or 1 for true.");
		}

		lineCounter++;
	}
	else if (stringSub.compare("Spider Spawn-Rate") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back();
		waveRef->SetSpiderSpawnRateWave((float)valueSecondHalf);

		lineCounter++;
	}
	else if (stringSub.compare("Spider Speed") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back();

		if ((float)valueSecondHalf == speedCantEqualZeroCheck)
		{
			ConsoleMsg::ShowError("At file line number " + Tools::ToString(lineNum) + " got 0 for Spider Speed. Ensure speed is a value greater than zero");
		}
		else
		{
			waveRef->SetSpiderSpeedWave((float)valueSecondHalf);

			lineCounter++;
		}
		
	}
	else if (stringSub.compare("Scorpion Present") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back();

		if (valueSecondHalf == 0)
		{
			waveRef->SetScorpPresentWave(false);
		}
		else if (valueSecondHalf == 1)
		{
			waveRef->SetScorpPresentWave(true);
		}
		else
		{
			ConsoleMsg::ShowError("At file line number " + Tools::ToString(lineNum) + "Scorpion Present needs to be either 0 for false or 1 for true.");
		}

		lineCounter++;
	}
	else if (stringSub.compare("Scorpion Spawn-Rate") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back();
		waveRef->SetScorpSpawnRateWave((float)valueSecondHalf);

		lineCounter++;
	}
	else if (stringSub.compare("Scorpion Speed") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back();

		if ((float)valueSecondHalf == speedCantEqualZeroCheck)
		{
			ConsoleMsg::ShowError("At file line number " + Tools::ToString(lineNum) + " got 0 for Scorpion Speed. Ensure speed is a value greater than zero");
		}
		else
		{
			waveRef->SetScorpSpeedWave((float)valueSecondHalf);

			lineCounter++;
		}

		
	}
	else if (stringSub.compare("Flea Present") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back();

		ConsoleMsg::WriteLine(Tools::ToString(valueSecondHalf));

		if (valueSecondHalf == 0)
		{
			waveRef->SetFleaPresentWave(false);
		}
		else if (valueSecondHalf == 1)
		{
			waveRef->SetFleaPresentWave(true);
		}
		else
		{
			ConsoleMsg::ShowError("At file line number " + Tools::ToString(lineNum) + "Flea Present needs to be either 0 for false or 1 for true.");
		}

		lineCounter++;
	}
	else if (stringSub.compare("Flea mushrooms required to spawn") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back();
		waveRef->SetFleaMushTriggerWave(valueSecondHalf);

		lineCounter++;
	}
	else if (stringSub.compare("Flea chance to trigger mushroom spawn") == 0)
	{
		//Set the new parameter for the current wave
		waveRef = waveList.back();
		waveRef->SetFleaChanceToTriggerMushSpawn(valueSecondHalf);

		lineCounter++;
	}
	else
	{
		ConsoleMsg::ShowError("At file line number " + Tools::ToString(lineNum) + " attempted to find some matching text but did not find any valid options. Attempted to match against: '" + readString + "'");
	}
}

WaveManager::~WaveManager()
{
	for (auto it = waveList.begin(); it != waveList.end(); ++it) {
		delete* it;
	}
	waveList.clear();
}