#ifndef _CtrlMgr
#define _CtrlMgr

#include "TEAL\CommonElements.h"
#include <vector>

//Forward declare to avoid input loop
class Blaster;
class ControllerBase;

class ControllerManager
{
public:
	ControllerManager();
	ControllerManager& operator=(const ControllerManager&) = delete;
	ControllerManager(ControllerManager& _copyBlaster) = delete;
	~ControllerManager();

	//Static definition of controller types accepted in the game
	const enum ControlType { AI, KEYBOARD};

	//Tell the controller manager to create a controller based on the ControlType
	ControllerBase* CreateController(ControlType _setType);

	ControllerBase* GetControllerByEnum(ControllerManager::ControlType ctrlType);

private:
	std::vector<ControllerBase*> CtrlList;

	const int ctrlListSize = 2;
};

#endif