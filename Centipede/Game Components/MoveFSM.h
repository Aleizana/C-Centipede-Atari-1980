#ifndef _MoveFSM
#define _MoveFSM

//Centipede
class MoveRightEndDownwards;
class MoveRightEndUpwards;
class MoveLeftEndDownwards;
class MoveLeftEndUpwards;
class TurnDownSwitchToLeft;
class TurnDownSwitchToRight;
class TurnUpSwitchToLeft;
class TurnUpSwitchToRight;
class PoisonedTurnDownEndLeft;
class PoisonedTurnDownEndRight;

//Spider
class SpiderMoveDown;
class SpiderMoveUp;
class SpiderMoveDownDiagRight;
class SpiderMoveDownDiagLeft;
class SpiderMoveUpDiagRight;
class SpiderMoveUpDiagLeft;
class SpiderMoveState;

//Blaster AI
class BlasterAIMoveDownDiagRight;
class BlasterAIMoveDownDiagLeft;
class BlasterAIMoveUpDiagRight;
class BlasterAIMoveUpDiagLeft;


class MoveFSM
{
private:
	

	
	
public:
	//Centipede
	static const MoveRightEndDownwards StateMoveRightEndDownwards;
	static const MoveRightEndUpwards StateMoveRightEndUpwards;
	static const MoveLeftEndDownwards StateMoveLeftEndDownwards;
	static const MoveLeftEndUpwards StateMoveLeftEndUpwards;
	static const TurnDownSwitchToLeft StateTurnDownSwitchToLeft;
	static const TurnDownSwitchToRight StateTurnDownSwitchToRight;
	static const TurnUpSwitchToLeft StateTurnUpSwitchToLeft;
	static const TurnUpSwitchToRight StateTurnUpSwitchToRight;
	static const PoisonedTurnDownEndLeft StatePoisonedTurnDownEndLeft;
	static const PoisonedTurnDownEndRight StatePoisonedTurnDownEndRight;

	//Blaster AI
	static const BlasterAIMoveDownDiagRight StateBlasterAIMoveDownDiagRight;
	static const BlasterAIMoveDownDiagLeft StateBlasterAIMoveDownDiagLeft;
	static const BlasterAIMoveUpDiagLeft StateBlasterAIMoveUpDiagLeft;
	static const BlasterAIMoveUpDiagRight StateBlasterAIMoveUpDiagRight;

	//Spider
	static const SpiderMoveDown StateSpiderMoveDown;
	static const SpiderMoveUp StateSpiderMoveUp;
	static const SpiderMoveDownDiagRight StateSpiderMoveDownDiagRight;
	static const SpiderMoveDownDiagLeft StateSpiderMoveDownDiagLeft;
	static const SpiderMoveUpDiagLeft StateSpiderMoveUpDiagLeft;
	static const SpiderMoveUpDiagRight StateSpiderMoveUpDiagRight;
};

#endif