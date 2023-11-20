// CentipedeHeadFactory
// Andre Berthiaume, April SlowSpeed013

#include "CentipedeHeadFactory.h"
#include "TEAL\CommonElements.h"
#include "CentipedeHeadObjectPool.h"
#include "CentipedeHead.h"
#include "CentipedeBody.h"
#include "CentipedeBodyFactory.h"
#include "MovementCollection.h"
#include "MoveFSM.h"
#include "ScoreManager.h"
#include "CmdScore.h"
#include "GridManager.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "LoopSoundCommand.h"
#include "PlaySoundCommand.h"
#include "PlayerManager.h"
#include "MovementCollection.h"

CentipedeHeadFactory* CentipedeHeadFactory::ptrInstance = nullptr;

CentipedeHeadFactory::CentipedeHeadFactory()
{
	//Get the CentipedeHead death score command from the score manager
	ConsoleMsg::WriteLine("CentipedeHead Factory:: Getting CentipedeHead Death Score Command");
	pDeath = GameManager::GetScoreMgr()->GetScoreCommand(GameManager::GetScoreMgr()->ScoreEvents::CentipedeHeadKilled);

	//Initialize the number of centipede heads to be zero upon init
	headCount = 0;

	spawnedInPlayerArea = false;
}

CentipedeHead* CentipedeHeadFactory::privCreateCentipedeHead(sf::Vector2f pos, int row, int col, const MoveState* setState, float speed, CentipedeBody* firstNode, int offsetIncr)
{
	CentipedeHead* CentipedeHeadRef;

	CentipedeHeadRef = myCentipedeHeadPool.GetCentipedeHead();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	CentipedeHeadRef->SetExternalManagement(RecycleCentipedeHead);

	//Initialize the new CentipedeHead
	CentipedeHeadRef->Initialize(pos, row, col, setState, firstNode, offsetIncr, speed);

	//Increment the number of heads present in the game
	Instance().headCount++;

	return CentipedeHeadRef;
}

void CentipedeHeadFactory::privRecycleCentipedeHead(GameObject* _CentipedeHeadRef)
{
	myCentipedeHeadPool.ReturnCentipedeHead(static_cast<CentipedeHead*>(_CentipedeHeadRef));

	ConsoleMsg::WriteLine("Main scene boolean: " + Tools::ToString(GameManager::MainSceneProcessing()));
	ConsoleMsg::WriteLine("Body Count: " + Tools::ToString(CentipedeBodyFactory::GetBodyCount()));
	ConsoleMsg::WriteLine("Head Count: " + Tools::ToString(Instance().headCount));

	if (Instance().headCount + CentipedeBodyFactory::GetBodyCount() <= 0 && GameManager::MainSceneProcessing() == true)
	{
		//Use a static cast to call the Loop Sound function to stop the loop now that there are no more centipedes
		static_cast<LoopSoundCommand*>(pSound)->StopLoop();
		GameManager::NotifyWaveComplete();
	}
}

void CentipedeHeadFactory::Terminate()
{
	delete Instance().pDeath;
	delete Instance().pSound;
	//delete Instance().pDeathSound;

	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}

void CentipedeHeadFactory::privLevelStartSpawn(int bodySpawnNumNodes, int numSoloHeads)
{
	spawnedInPlayerArea = false;

	//Reset the counters for both of the factories
	headCount = 0;
	CentipedeBodyFactory::ResetBodyCount();

	//Send the sound command for centipede movement
	privSendSoundCommand();

	//Get the row and column of the centipede head by dividing their pixel pos by the cell size of the grid
	//Casting is safe given that the X and Y pixel position in which the head will spawn must be divisible by the whole number cell size
	int headCol = (int)X_SpawnMainCentipede / GameManager::GetGridMgr()->GetPixelDistance();
	int headRow = (int)Y_SpawnTopOfScreen / GameManager::GetGridMgr()->GetPixelDistance();

	//Offset to add to the x and y of the pos of a centipede obj so that they can start within the middle of a cell
	float spawnGridOffset = (float)(GameManager::GetGridMgr()->GetPixelDistance() / GameManager::GetGridMgr()->GetPixelDistanceOffset());

	//Initialize the spawn position of the head of the centipede at the beginning of a level, with offset based on the cell size / dimensions of the grid
	float headSpawn_X = X_SpawnMainCentipede + spawnGridOffset;
	float headSpawn_Y = Y_SpawnTopOfScreen - spawnGridOffset;

	//Holds the x and y spawn pos plus the offset of the centipede head
	sf::Vector2f headSpawnPos = sf::Vector2f(headSpawn_X, headSpawn_Y);
	
	//Create a centipede head with default values 
	CentipedeHead* tmpHeadRef = privCreateCentipedeHead(headSpawnPos, headRow, headCol, (MoveState*)&MoveFSM::StateTurnDownSwitchToRight, centiSpeed, nullptr, 0);

	//Incrementing values to offset each centipede body node based off the last
	int rowDecHold = 0;
	float ySpawnOffSetHold = 0;

	CentipedeBody* bodyRef;
	CentipedeBody* holdPrevBody = nullptr;

	//Create the body nodes of the main centipede
	for (int i = 0; i < bodySpawnNumNodes; i++)
	{
		rowDecHold += BodySpawn_RowDecrement;
		ySpawnOffSetHold += GameManager::GetGridMgr()->GetPixelDistance();

		headSpawnPos.y = headSpawn_Y - ySpawnOffSetHold;

		bodyRef = CentipedeBodyFactory::CreateCentipedeBody(headSpawnPos, headRow - rowDecHold, headCol, tmpHeadRef, holdPrevBody, centiSpeed);

		//If there is a previous body node being held, set it's next ptr to be pointing to the newly created body node
		if (holdPrevBody != nullptr)
		{
			holdPrevBody->SetNextPtr(bodyRef);
		}
		//If this is the first node to be created, set the head to point to that first body node
		else if (i == 0)
		{
			tmpHeadRef->SetBodyNodePtr(bodyRef);
		}

		//Set the previous body to be the newly created one
		holdPrevBody = bodyRef;


	}

	headRow = (int)Y_SpawnTopOfScreen / GameManager::GetGridMgr()->GetPixelDistance();

	if (soloHeadsPresent)
	{
		int numSoloHeadSpawn;

		//Check to make sure the number of solo heads doesnt exceed the amount of centipede heads allowed to spawn at the top of the screen
		if (numSoloHeads > soloHeadMaxPerSpawn)
		{
			numSoloHeadSpawn = soloHeadMaxPerSpawn;
		}
		else
		{
			numSoloHeadSpawn = numSoloHeads;
		}

		//Create each of the solo heads using previously declared variables
		for (int i = 0; i < numSoloHeadSpawn; i++)
		{
			//Spawn heads in increments of the cell size
			headSpawn_X = (float)((GameManager::GetGridMgr()->GetPixelDistance() * (soloHeadSpawnOffset * i)));

			//Get the column of the centipede head by dividing their pixel pos by the cell size of the grid
			//Casting is safe given that the X pixel position in which the head will spawn must be divisible by the whole number cell size
			headCol = (int)headSpawn_X / GameManager::GetGridMgr()->GetPixelDistance();

			//Initialize the spawn position of the head of the centipede at the beginning of a level, with offset based on the cell size / dimensions of the grid
			headSpawn_X += spawnGridOffset;

			//Holds the x and y spawn pos plus the offset of the centipede head
			headSpawnPos = sf::Vector2f(headSpawn_X, Y_SpawnTopOfScreen - spawnGridOffset);

			//Create a centipede head with default values 
			tmpHeadRef = privCreateCentipedeHead(headSpawnPos, headRow, headCol, (MoveState*)&MoveFSM::StateTurnDownSwitchToRight, soloHeadSpeed, nullptr, 0);
		}
	}
	
}

const float CentipedeHeadFactory::privGetHeadSpeed() const
{
	return centiSpeed;
}

void CentipedeHeadFactory::privSetHeadSpeed(float setSpeed)
{
	if (MovementCollection::GetArrMax() % (int)setSpeed == 0 && setSpeed < MovementCollection::GetArrMax())
	{
		centiSpeed = setSpeed;
	}
	else
	{
		if (setSpeed > FastSpeed)
		{
			centiSpeed = FastSpeed;
		}
		else if (setSpeed > MediumSpeed)
		{
			centiSpeed = MediumSpeed;
		}
		else if (setSpeed > SlowSpeed)
		{
			centiSpeed = SlowSpeed;
		}
	}
	
}

void CentipedeHeadFactory::privResetHeadCount()
{
	headCount = 0;
}

void CentipedeHeadFactory::privSendDeathCommandForScore()
{
	//Pass the score command to the manager so that it can create a command score instance
	GameManager::GetScoreMgr()->SendScoreCmd(pDeath);
}

void CentipedeHeadFactory::privDecrementHeadCount()
{
	ConsoleMsg::WriteLine("Head count before decrement: " + Tools::ToString(headCount));

	headCount--;
}

void CentipedeHeadFactory::privSendSoundCommand()
{
	GameManager::GetSoundManager()->SendSoundCmd(pSound);
}

void CentipedeHeadFactory::privStoreSoundCommand()
{
	pSound = GameManager::GetSoundManager()->GetSoundCommand(GameManager::GetSoundManager()->SoundEvents::CentipedeLoop);
}

void CentipedeHeadFactory::privStopCentiLoop()
{
	//Use a static cast to call the Loop Sound function to stop the loop now that there are no more centipedes
	static_cast<LoopSoundCommand*>(pSound)->StopLoop();
}

const int CentipedeHeadFactory::privGetCentiDrawOrder()
{
	return CentipedeDrawOrder;
}

void CentipedeHeadFactory::privSetSoloHeadPresent(bool status)
{
	soloHeadsPresent = status;
}

void CentipedeHeadFactory::privSetSoloHeadSpeed(float speed)
{
	if (MovementCollection::GetArrMax() % (int)speed == 0 && speed < MovementCollection::GetArrMax())
	{
		soloHeadSpeed = speed;
	}
	else
	{
		if (speed > FastSpeed)
		{
			soloHeadSpeed = FastSpeed;
		}
		else if (speed > MediumSpeed)
		{
			soloHeadSpeed = MediumSpeed;
		}
		else if (speed > SlowSpeed)
		{
			soloHeadSpeed = SlowSpeed;
		}
	}
	
}

void CentipedeHeadFactory::privSetSoloHeadPresentPlrArea(bool status)
{
	soloHeadsPresentPlrArea = status;
}

void CentipedeHeadFactory::privSetSoloHeadPlrAreaCount(int count)
{
	if (count > soloHeadMaxPerSpawn)
	{
		soloHeadSpawnInPlrAreaCount = soloHeadMaxPerSpawn;
	}
	else
	{
		soloHeadSpawnInPlrAreaCount = count;
	}
	
}

void CentipedeHeadFactory::privSpawnPlrAreaSoloHeads()
{
	if (soloHeadsPresentPlrArea && !spawnedInPlayerArea)
	{
		spawnedInPlayerArea = true;

		int headCol;

		int headRow;

		sf::Vector2f headSpawnPos;

		CentipedeHead* tmpHeadRef;

		//Offset to add to the x and y of the pos of a centipede obj so that they can start within the middle of a cell
		float spawnGridOffset = (float)(GameManager::GetGridMgr()->GetPixelDistance() / GameManager::GetGridMgr()->GetPixelDistanceOffset());

		float headSpawnX = (float)(leftSideOfScreen_Col * GameManager::GetGridMgr()->GetPixelDistance());

		float headSpawnY_Base = (float)GameManager::GetPlayerMgr()->GetPlayerAreaLimit(); 

		const int halfCount = soloHeadSpawnInPlrAreaCount / SoloHeadPlrAreaCountDivisor;

		float holdIncYPos = headSpawnY_Base;

		//Spawning on the left side of the player area
		for (int i = 0; i < halfCount; i++)
		{
			//Initialize the spawn position of the head of the centipede at the beginning of a level, with offset based on the cell size / dimensions of the grid
			holdIncYPos = headSpawnY_Base + (GameManager::GetGridMgr()->GetPixelDistance() * i);

			//Get the row and column of the centipede head by dividing their pixel pos by the cell size of the grid
			//Casting is safe given that the X and Y pixel position in which the head will spawn must be divisible by the whole number cell size
			headRow = (int)holdIncYPos / GameManager::GetGridMgr()->GetPixelDistance();

			//Holds the x and y spawn pos plus the offset of the centipede head
			headSpawnPos = sf::Vector2f(headSpawnX + spawnGridOffset, holdIncYPos - spawnGridOffset);

			//Create a centipede head with default values 
			tmpHeadRef = privCreateCentipedeHead(headSpawnPos, headRow, leftSideOfScreen_Col, (MoveState*)&MoveFSM::StateMoveRightEndDownwards, soloHeadPlrAreaSpeed, nullptr, 0);
		}

		//The heads on the right side of the screen will start at the last column
		headCol = GameManager::GetGridMgr()->GetNumCols();

		//Get the right side of the screen pos
		headSpawnX = (float)(GameManager::GetGridMgr()->GetPixelDistance() * headCol);

		//To count the offset of heads from the first spawn position
		int yOffsetCount = 0;

		//Reset the incrementor position to be at the base y-spawn value
		holdIncYPos = headSpawnY_Base;

		//Spawning on the right side of the player area with the second half of the solo heads
		for (int i = halfCount; i < soloHeadSpawnInPlrAreaCount; i++)
		{
			//Increment the ypos based on the number of solo heads spawned so far
			holdIncYPos = headSpawnY_Base + (GameManager::GetGridMgr()->GetPixelDistance() * yOffsetCount);

			//Get the row and column of the centipede head by dividing their pixel pos by the cell size of the grid
			//Casting is safe given that the X and Y pixel position in which the head will spawn must be divisible by the whole number cell size
			headRow = (int)holdIncYPos / GameManager::GetGridMgr()->GetPixelDistance();

			//Holds the x and y spawn pos plus the offset of the centipede head
			headSpawnPos = sf::Vector2f(headSpawnX + spawnGridOffset, holdIncYPos - spawnGridOffset);

			//Create a centipede head with default values 
			tmpHeadRef = privCreateCentipedeHead(headSpawnPos, headRow, headCol, (MoveState*)&MoveFSM::StateMoveLeftEndDownwards, soloHeadPlrAreaSpeed, nullptr, 0);

			//Increment the number of solo heads spawned for the y-offset from the base spawn pos
			yOffsetCount++;
		}

		
	}
}

void CentipedeHeadFactory::privSetSoloHeadPlrAreaSpeed(float speed)
{
	if (MovementCollection::GetArrMax() % (int)speed == 0 && speed < MovementCollection::GetArrMax())
	{
		soloHeadPlrAreaSpeed = speed;
	}
	else
	{
		if (speed > FastSpeed)
		{
			soloHeadPlrAreaSpeed = FastSpeed;
		}
		else if (speed > MediumSpeed)
		{
			soloHeadPlrAreaSpeed = MediumSpeed;
		}
		else if (speed > SlowSpeed)
		{
			soloHeadPlrAreaSpeed = SlowSpeed;
		}
	}
	

	
}
