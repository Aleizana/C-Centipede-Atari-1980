#ifndef _Wave
#define _Wave

//Forward declarations of all of the game's "enemies"


class Wave
{
public:
	Wave() = default;
	Wave& operator= (const Wave&) = delete;
	Wave(const Wave& copyWave) = delete;
	~Wave() = default;

	const int GetCentiLenWave() const;
	void SetCentiLenWave(int len);
	const float GetCentiSpeedWave() const;
	void SetCentiSpeedWave(float speed);

	const int GetCentiSingleHeadSpawnWave() const;
	void SetCentiSingleHeadSpawnWave(int headSpawnCount);
	bool GetSingleHeadPresent();
	void SetSingleHeadPresent(bool present);
	bool GetSingleHeadPresentInPlrArea();
	void SetSingleHeadPresentInPlrArea(bool present);
	int GetSingleHeadSpawnInPlrAreaCount();
	void SetSingleHeadSpawnInPlrAreaCount(int count);
	float GetSoloHeadSpeed();
	void SetSoloHeadSpeed(float speed);
	float GetSoloHeadPlrAreaSpeed();
	void SetSoloHeadPlrAreaSpeed(float speed);

	const bool GetSpiderPresentWave() const;
	void SetSpiderPresentWave(bool present);
	const float GetSpiderSpawnRateWave() const;
	void SetSpiderSpawnRateWave(float spawnRate);
	const float GetSpiderSpeedWave() const;
	void SetSpiderSpeedWave(float speed);

	const bool GetFleaPresentWave() const;
	void SetFleaPresentWave(bool present);
	const int GetFleaNumMushToTriggerWave() const;
	void SetFleaMushTriggerWave(int mushNum);
	int GetFleaChanceToTriggerMushSpawn() const;
	void SetFleaChanceToTriggerMushSpawn(int chanceToTrigger);

	const bool GetScorpionPresentWave() const;
	void SetScorpPresentWave(bool present);
	const float GetScorpionSpawnRateWave() const;
	void SetScorpSpawnRateWave(float spawnRate);
	const float GetScorpionSpeedWave() const;
	void SetScorpSpeedWave(float speed);

private:
	//Centipede data
	//Size of an int for the length of the centipede
	int centiLen;

	//Size of a float for the speed of the centipede heads/body
	float centiSpeed;

	//Solo Centipede Data
	bool soloHeadsPresent;
	//Size of an int for the number of single centipede heads that will spawn
	int centiSingleHeadSpawn;
	//If the solo heads will be present once the centipede has reached the bottom of the screen
	bool soloHeadPlayerAreaSpawn;
	//The number of solo heads that will spawn in the plr area once the centipede has reached the bottom
	int numSoloHeadPlrArea;
	//The speed of the solo heads
	float soloHeadSpeed;
	//Speed of solo heads spawned in the player area
	float soloHeadPlrAreaSpeed;

	//Spider data
	bool spiderPresent;

	float spiderSpawnRate;

	float spiderSpeed;

	//Flea Data
	bool fleaPresent;

	int fleaNumMushToTrigger;

	int fleaChanceToTriggerMushSpawn;

	//Scorpion Data
	bool scorpionPresent;

	float scorpionSpawnRate;

	float scorpionSpeed;
};

#endif
