#include "ControllerManager.h"
#include "ControllerBase.h"
#include "BlasterKeyboardController.h"
#include "BlasterAIController.h"

ControllerManager::ControllerManager()
{
	CtrlList.assign(ctrlListSize, nullptr);
}

ControllerManager::~ControllerManager()
{
	for (ControllerBase* ctrl : CtrlList)
	{
		delete ctrl;
	}
}

ControllerBase* ControllerManager::CreateController(ControlType _setType)
{
	ControllerBase* newCtrlRef = nullptr;

	//If the controller has already been created
	if (CtrlList.at((int)_setType) != nullptr)
	{
		newCtrlRef = CtrlList.at((int)_setType);
	}
	else if (_setType == ControlType::KEYBOARD)
	{
		CtrlList.at((int)_setType) = (ControllerBase*)new BlasterKeyboardController;
		newCtrlRef = CtrlList.at((int)_setType);
	}
	else if (_setType == ControlType::AI)
	{
		CtrlList.at((int)_setType) = (ControllerBase*)new BlasterAIController;
		newCtrlRef = CtrlList.at((int)_setType);
	}

	return newCtrlRef;
}

ControllerBase* ControllerManager::GetControllerByEnum(ControllerManager::ControlType ctrlType)
{
	assert((int)ctrlType < (int)CtrlList.size() && "Attempted to grab a controller that didnt exist yet");
	

	return CtrlList.at((int)ctrlType);

}