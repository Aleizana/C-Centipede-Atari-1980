// CentipedeLevel
// Andre Berthiaume, MArch 2013

#include "TEAL\CommonElements.h"

#include "AttractorMode.h"
#include "Flea.h"
#include "Dart.h"
#include "Mushroom.h"
#include "Blaster.h"
#include "Scorpion.h"
#include "Spider.h"
#include "CentipedeHead.h"
#include "CentipedeBody.h"
#include "MushroomFactory.h"
#include "GameManager.h"
#include "Glyph.h"

void AttractorMode::Initialize()
{
	//Initializes the player at the beginning of a scene
	GameManager::SceneStartInit();

	//Create the mushroom field at the start of the game
	MushroomFactory::InitMushroomField();

	CollisionTestPair<Dart, Mushroom>();
	CollisionTestPair<Blaster, Mushroom>();
	CollisionTestPair<Blaster, Flea>();
	CollisionTestPair<Dart, Flea>();
	CollisionTestPair<Dart, Scorpion>();
	CollisionTestPair<Dart, CentipedeHead>();
	CollisionTestPair<Blaster, CentipedeHead>();
	CollisionTestPair<Dart, CentipedeBody>();
	CollisionTestPair<Blaster, CentipedeBody>();
	CollisionTestPair<Blaster, Spider>();
	CollisionTestPair<Spider, Dart>();
	CollisionTestPair<Spider, Mushroom>();
	CollisionTestPair<Dart, Glyph>();
};

void AttractorMode::Terminate()
{

}


