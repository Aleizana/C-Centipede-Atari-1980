// MushroomFactory
// Andre Berthiaume, April 2013

#include "MushroomFactory.h"
#include "TEAL\CommonElements.h"
#include "MushroomObjectPool.h"
#include "Mushroom.h"
#include "BlasterFactory.h"
#include "Grid.h"
#include "ScoreManager.h"
#include "CmdScore.h"
#include "PlayerManager.h"
#include "GridManager.h"
#include "Player.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "PlaySoundCommand.h"
#include "SoundCommand.h"

MushroomFactory* MushroomFactory::ptrInstance = nullptr;

MushroomFactory::MushroomFactory()
	: pSound(nullptr), pMushDeath(GameManager::GetScoreMgr()->GetScoreCommand(GameManager::GetScoreMgr()->ScoreEvents::MushroomKilled)), 
		pPoisonMushDeath(GameManager::GetScoreMgr()->GetScoreCommand(GameManager::GetScoreMgr()->ScoreEvents::MushroomPoisonKilled)),
			pMushRegen(GameManager::GetScoreMgr()->GetScoreCommand(GameManager::GetScoreMgr()->ScoreEvents::MushroomRegeneration))
{
	//Get the Mushroom death score commands from the score manager
	ConsoleMsg::WriteLine("Mushroom Factory:: Getting Mushroom Death Score Command");
	ConsoleMsg::WriteLine("Mushroom Factory:: Getting Poison Mushroom Death Score Command");
	ConsoleMsg::WriteLine("Mushroom Factory:: Getting Poison Mushroom Regen Score Command");
}

bool MushroomFactory::privCreateMushroom(int row, int col)
{
	//Mushrooms can not be spawned in the first row
	if (row != GameManager::GetGridMgr()->GetRowStartIndex())
	{
		//Check if a mushroom can be spawned at the given position in the grid, spawn mushroom and return true if open
		if (GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->CheckGridSpot(row, col) == GameGrid::CheckGridResult::OPEN)
		{
			Mushroom* mushroomRef;

			//Else continue creating a new Mushroom from the pool
			mushroomRef = myMushroomPool.GetMushroom();

			// Declares that this object should be returned here (rather than deleted) when destroyed
			mushroomRef->SetExternalManagement(RecycleMushroom);

			//Store the cell size of the grid
			int cellSizeRef = GameManager::GetGridMgr()->GetPixelDistance();

			//Get the offset from the sides of a cell so that the mushroom can spawn in the middle of a cell
			int mushPixelOffset = cellSizeRef / GameManager::GetGridMgr()->GetPixelDistanceOffset();

			sf::Vector2f pos = sf::Vector2f((float)(cellSizeRef * col) + mushPixelOffset, (float)(cellSizeRef * row) - mushPixelOffset);

			//Initialize the new Mushroom
			mushroomRef->Initialize(pos);

			//In order to not have the grid be directly tied to constructor of the mushroom, row and column will be set in a separate function
			mushroomRef->SetRowCol(row, col);

			//Pass the newly created mushroom the grid so that it can have a reference
			GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->PassGameObjectRef(row, col, mushroomRef);

			mushCount++;

			return true;
		}
	}
	

	//If mushroom can not be spawned, return false
	return false;

	
}

void MushroomFactory::privRecycleMushroom(GameObject* _mushroomRef)
{
	myMushroomPool.ReturnMushroom(static_cast<Mushroom*>(_mushroomRef));
	Instance().mushCount--;
}

void MushroomFactory::Terminate()
{
	//Delete the score commands
	delete Instance().pMushDeath;
	delete Instance().pPoisonMushDeath;
	delete Instance().pMushRegen;

	delete Instance().pSound;

	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}

void MushroomFactory::privInitMushroomField()
{
	//For counting grid indices
	int rowStartIndex = GameManager::GetGridMgr()->GetRowStartIndex();
	
	int cellSizeRef = GameManager::GetGridMgr()->GetPixelDistance();
	
	//Get the offset from the sides of a cell so that the mushroom can spawn in the middle of a cell
	int mushPixelOffset = cellSizeRef / GameManager::GetGridMgr()->GetPixelDistanceOffset();
	
	//Initialize the number of mushrooms present to zero
	mushCount = 0;
	
	//Get the blaster's spawn pos in grid by dividing it's pos by the cell size of the grid
	sf::Vector2f holdBlastSpawn = BlasterFactory::GetBlasterSpawnPos();
	int blasterRow = (int)holdBlastSpawn.y / cellSizeRef;
	int blasterCol = (int)holdBlastSpawn.x / cellSizeRef;
	
	//Iterate through every row to see where to spawn mushrooms
	//Num rows + starting row index to consider the property of the grid where the row index starts at 1
	for (int rowIter = mushroomFirstRowToSpawn; rowIter < GameManager::GetGridMgr()->GetNumRows() + rowStartIndex; rowIter++)
	{
		//Get a random number between the min and the max number of mushrooms allowed to be created in the row
		int mushNum = rand() % maxMushSpawnRow;
	
		//Iterate and randomize where to spawn mushrooms based on the number of mushrooms randomly selected to be spawned
		for (int mushIter = minMushSpawnRow; mushIter < mushNum; mushIter++)
		{
			//Randomly select a position between 0 and the number of columns in the game grid
			int randCol = rand() % GameManager::GetGridMgr()->GetNumCols();
	
			//If the row and column are not the position of the blaster
			if (rowIter != blasterRow && randCol != blasterCol)
			{
				//Query grid to see if the space selected is open
				if (GameManager::GetPlayerMgr()->GetActivePlayer()->GetPlayerGrid()->CheckGridSpot(rowIter, randCol) == GameGrid::CheckGridResult::OPEN)
				{
					privCreateMushroom(rowIter, randCol);
				}
			}
		}
	}
}

void MushroomFactory::privSendDeathCommandForScore_NoPoison()
{
	//Pass the score command to the manager so that it can create a command score instance
	GameManager::GetScoreMgr()->SendScoreCmd(pMushDeath);
}

void MushroomFactory::privSendDeathCommandForScore_Poison()
{
	//Pass the score command to the manager so that it can create a command score instance
	GameManager::GetScoreMgr()->SendScoreCmd(pPoisonMushDeath);
}

void MushroomFactory::privSendMushroomRegenScoreCommand()
{
	//Pass the score command to the manager so that it can create a command score instance
	GameManager::GetScoreMgr()->SendScoreCmd(pMushRegen);
}

void MushroomFactory::privSendSoundCommand()
{
	GameManager::GetSoundManager()->SendSoundCmd(pSound);
}

void MushroomFactory::privStoreSoundCommand()
{
	pSound = GameManager::GetSoundManager()->GetSoundCommand(GameManager::GetSoundManager()->SoundEvents::MushroomRegen);
}
