// GameOverScene

#ifndef _GameOverScene
#define _GameOverScene

#include "TEAL\CommonElements.h"


class GameOverScene : public Scene
{
public:
	GameOverScene() = default;
	GameOverScene(const GameOverScene&) = delete;
	GameOverScene& operator=(const GameOverScene&) = delete;
	~GameOverScene() = default;

	virtual void Initialize();
	virtual void Terminate();



private:
};

#endif _GameOverScene