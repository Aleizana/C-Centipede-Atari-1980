#include "Wave.h"

const int Wave::GetCentiLenWave() const
{
	return centiLen;
}

void Wave::SetCentiLenWave(int len)
{
	centiLen = len;
}

const float Wave::GetCentiSpeedWave() const
{
	return centiSpeed;
}

void Wave::SetCentiSpeedWave(float speed)
{
	if (speed == 0)
	{
		centiSpeed = 1.0f;
	}

	centiSpeed = speed;
}

const int Wave::GetCentiSingleHeadSpawnWave() const
{
	return centiSingleHeadSpawn;
}

void Wave::SetCentiSingleHeadSpawnWave(int headSpawnCount)
{
	centiSingleHeadSpawn = headSpawnCount;
}

bool Wave::GetSingleHeadPresent()
{
	return soloHeadsPresent;
}

void Wave::SetSingleHeadPresent(bool present)
{
	soloHeadsPresent = present;
}

bool Wave::GetSingleHeadPresentInPlrArea()
{
	return soloHeadPlayerAreaSpawn;
}

void Wave::SetSingleHeadPresentInPlrArea(bool present)
{
	soloHeadPlayerAreaSpawn = present;
}

int Wave::GetSingleHeadSpawnInPlrAreaCount()
{
	return numSoloHeadPlrArea;
}

void Wave::SetSingleHeadSpawnInPlrAreaCount(int count)
{
	numSoloHeadPlrArea = count;
}

float Wave::GetSoloHeadSpeed()
{
	return soloHeadSpeed;
}

void Wave::SetSoloHeadSpeed(float speed)
{
	soloHeadSpeed = speed;
}

float Wave::GetSoloHeadPlrAreaSpeed()
{
	return soloHeadPlrAreaSpeed;
}

void Wave::SetSoloHeadPlrAreaSpeed(float speed)
{
	soloHeadPlrAreaSpeed = speed;
}

const bool Wave::GetSpiderPresentWave() const
{
	return spiderPresent;
}

void Wave::SetSpiderPresentWave(bool present)
{
	spiderPresent = present;
}

const float Wave::GetSpiderSpawnRateWave() const
{
	return spiderSpawnRate;
}

void Wave::SetSpiderSpawnRateWave(float spawnRate)
{
	spiderSpawnRate = spawnRate;
}

const float Wave::GetSpiderSpeedWave() const
{
	return spiderSpeed;
}

void Wave::SetSpiderSpeedWave(float speed)
{
	spiderSpeed = speed;
}

const bool Wave::GetFleaPresentWave() const
{
	return fleaPresent;
}

void Wave::SetFleaPresentWave(bool present)
{
	fleaPresent = present;
}

const int Wave::GetFleaNumMushToTriggerWave() const
{
	return fleaNumMushToTrigger;
}

void Wave::SetFleaMushTriggerWave(int mushNum)
{
	fleaNumMushToTrigger = mushNum;
}

int Wave::GetFleaChanceToTriggerMushSpawn() const
{
	return fleaChanceToTriggerMushSpawn;
}

void Wave::SetFleaChanceToTriggerMushSpawn(int chanceToTrigger)
{
	fleaChanceToTriggerMushSpawn = chanceToTrigger;
}

const bool Wave::GetScorpionPresentWave() const
{
	return scorpionPresent;
}

void Wave::SetScorpPresentWave(bool present)
{
	scorpionPresent = present;
}

const float Wave::GetScorpionSpawnRateWave() const
{
	return scorpionSpawnRate;
}

void Wave::SetScorpSpawnRateWave(float spawnRate)
{
	scorpionSpawnRate = spawnRate;
}

const float Wave::GetScorpionSpeedWave() const
{
	return scorpionSpeed;
}

void Wave::SetScorpSpeedWave(float speed)
{ 
	scorpionSpeed = speed;
}
