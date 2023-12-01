#ifndef _ScorpionMover
#define _ScorpionMover

#include "TEAL\CommonElements.h"

//Reference to the Scorpion will be used in many functions
class Scorpion;

class ScorpionMover
{
public:
	ScorpionMover();
	ScorpionMover& operator=(const ScorpionMover&) = delete;
	ScorpionMover(ScorpionMover& _copyBlaster) = delete;
	~ScorpionMover() = default;

	//Function that centipede head will call when it needs to be moved across the screen
	void HandleScorpionMove_Left(Scorpion* scorpionToMove, int& countMovement, int leftPrevCellCheck);

	//Function that centipede head will call when it needs to be moved across the screen
	void HandleScorpionMove_Right(Scorpion* scorpionToMove, int& countMovement, int leftPrevCellCheck);

	void SetScorpionSpeed(float speed);
	

private:
	//Scorpion game properties
	float scorpionSpeed;

	//The number of cells the scorpion will move every time row/col is updated
	const int ScorpGridMoveVal = 1;

	//Performs check for if the scorpion went off the screen in either the left or right direction
	bool HandleOffScreenCheck_Right(Scorpion* scorpionToMove, sf::Vector2f newPos);
	bool HandleOffScreenCheck_Left(Scorpion* scorpionToMove, sf::Vector2f newPos);

	//Performs actions required for when a scorpion is destroyed
	void HandleScorpionDestroy(Scorpion* scorpionToMove);
};

#endif