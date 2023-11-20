// LoadAllResources.cpp
// Andre Berthiaume, June 2012
//
// The user fills the method with all resources that need loading

#include "ResourceManager.h"
#include "../MainGameScene.h"
#include "../AttractorMode.h"
#include "../GameDataInitScene.h"

void ResourceManager::LoadAllResources()
{
	//Start the game in Attractor Mode with an AI player
	SetStartScene(new GameDataInitScene);

	AddTexture("blaster", "blaster.png");
	AddTexture("mushroom", "mushroom.png");
	AddTexture("flea", "flea.png");
	AddTexture("bullet", "bullet.png");
	AddTexture("centipede_head", "centipede_head.png");
	AddTexture("centipede_segment", "centipede_segment.png");
	AddTexture("scorpion", "scorpion.png");
	AddTexture("spider", "spider.png");
	AddTexture("explosion", "death.png");
	AddTexture("Alphabet", "FONTwPLAYER.bmp");
	AddTexture("FullSpriteList", "SPRITES.png");

	AddSound("ExtraLife", "extraLife.wav");
	AddSound("BlasterDeath", "death.wav");
	AddSound("MushroomRegen", "bonus.wav");
	AddSound("NonPlayerDeath", "kill.wav");
	AddSound("CentipedeMovement", "newBeat.wav");
	AddSound("ScorpionMovement", "scorpion_new.wav");
	AddSound("FleaMovement", "flea_new.wav");
	AddSound("SpiderMovement", "spiderloop.wav");
	AddSound("FireDart", "fire1.wav");
}

