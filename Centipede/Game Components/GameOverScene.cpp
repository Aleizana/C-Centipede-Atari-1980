// CentipedeLevel
// Andre Berthiaume, MArch 2013

#include "TEAL\CommonElements.h"

#include "GameOverScene.h"
#include "GameManager.h"
#include "Dart.h"
#include "Glyph.h"

void GameOverScene::Initialize()
{
	//Initializes the player at the beginning of a scene
	GameManager::SceneStartInitGameOver();

	CollisionTestPair<Dart, Glyph>();
};

void GameOverScene::Terminate()
{

}


