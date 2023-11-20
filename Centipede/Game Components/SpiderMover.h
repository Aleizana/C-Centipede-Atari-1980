#ifndef _SpiderMover
#define _SpiderMover

#include "TEAL\CommonElements.h"

//Reference to the Spider will be used in many functions
class Spider;
class SpiderMoveState;

//Essential for enum
#include "SpiderFactory.h"

class SpiderMover
{
public:
	SpiderMover();
	SpiderMover& operator=(const SpiderMover&) = delete;
	SpiderMover(SpiderMover& _copyBlaster) = delete;
	~SpiderMover() = default;

	//Function that centipede head will call when it needs to be moved across the screen
	void HandleSpiderMove(Spider* SpiderToMove, int& moveArrIncrementor);

	void SetSpiderSpeed(float speed);

private:
	

	//Random range and target values for each of the states to be randomly decided
	const int randValRange = 2;
	const int randTargetDownDiagLeft = 0;
	const int randTargetDownDiagRight = 0;
	const int randTargetUpDiagLeft = 1;
	const int randTargetUpDiagRight = 1;

	

	float holdSpeed;
};

#endif