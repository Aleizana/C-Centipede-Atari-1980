#ifndef _CtrlBase
#define _CtrlBase

#include "TEAL\CommonElements.h"
#include <vector>

//Forward declare to avoid input loop
class Blaster;

class ControllerBase
{
public:
	ControllerBase() = default;
	ControllerBase& operator=(const ControllerBase&) = delete;
	ControllerBase(ControllerBase& _copyBlaster) = delete;
	~ControllerBase() = default;

	//For the blaster to call every frame to do it's movements
	virtual void Update(sf::Vector2f& impulse, Blaster* playerRef) = 0;
	virtual void KeyPressed(Blaster* playerRef, sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey) = 0;

	virtual void Initialize() = 0;

private:
};

#endif