// MainGameScene

#ifndef _MainGameScene
#define _MainGameScene

#include "TEAL\CommonElements.h"


class MainGameScene : public Scene
{
public:
	MainGameScene() = default;
	MainGameScene(const MainGameScene&) = delete;
	MainGameScene& operator=(const MainGameScene&) = delete;
	~MainGameScene() = default;

	virtual void Initialize();
	virtual void Terminate();



private:
};

#endif _MainGameScene