// GameDataInitScene

#ifndef _GameDataInitScene
#define _GameDataInitScene

#include "TEAL\CommonElements.h"


class GameDataInitScene : public Scene
{
public:
	GameDataInitScene() = default;
	GameDataInitScene(const GameDataInitScene&) = delete;
	GameDataInitScene& operator=(const GameDataInitScene&) = delete;
	~GameDataInitScene() = default;

	virtual void Initialize();
	virtual void Terminate();



private:
};

#endif _GameDataInitScene