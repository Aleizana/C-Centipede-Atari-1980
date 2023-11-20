// CentipedeLevel
// Andre Berthiaume, MArch 2013

#include "TEAL\CommonElements.h"

#include "GameDataInitScene.h"
#include "GameManager.h"
#include "Dart.h"
#include "Glyph.h"

void GameDataInitScene::Initialize()
{
	//Initializes the player at the beginning of a scene
	GameManager::GameDataSceneInit();
};

void GameDataInitScene::Terminate()
{

}


