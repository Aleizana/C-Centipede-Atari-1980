// GameStart.cpp
// Andre Berthiaume, July 2019

#include "Game.h"
#include "../DartFactory.h"
#include "../BlasterFactory.h"
#include "../MushroomFactory.h"
#include "../FleaFactory.h"
#include "../ScorpionFactory.h"
#include "../CentipedeHeadFactory.h"
#include "../CentipedeBodyFactory.h"
#include "../SpiderFactory.h"
#include "../ScoreManager.h"
#include "../PlayerManager.h"
#include "../GridManager.h"
#include "../DisplayOnDeathFactory.h"
#include "../GameManager.h"
#include "../GlyphFactory.h"

void Game::GameEnd()
{
	DartFactory::Terminate();
	BlasterFactory::Terminate();
	MushroomFactory::Terminate();
	FleaFactory::Terminate();
	ScorpionFactory::Terminate();
	CentipedeHeadFactory::Terminate();
	CentipedeBodyFactory::Terminate();
	SpiderFactory::Terminate();
	DisplayOnDeathFactory::Terminate();
	GameManager::Terminate();
	GlyphFactory::Terminate();
}