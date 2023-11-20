#include "MoveFSM.h"
#include "MoveRightEndDownwards.h"
#include "MoveLeftEndDownwards.h"
#include "MoveRightEndUpwards.h"
#include "MoveLeftEndUpwards.h"
#include "TurnDownSwitchToLeft.h"
#include "TurnDownSwitchToRight.h"
#include "TurnUpSwitchToLeft.h"
#include "TurnUpSwitchToRight.h"
#include "PoisonedTurnDownEndLeft.h"
#include "PoisonedTurnDownEndRight.h"

#include "SpiderMoveDown.h"
#include "SpiderMoveUp.h"
#include "SpiderMoveDownDiagRight.h"
#include "SpiderMoveDownDiagLeft.h"
#include "SpiderMoveUpDiagRight.h"
#include "SpiderMoveUpDiagLeft.h"

#include "BlasterAIMoveDownDiagRight.h"
#include "BlasterAIMoveDownDiagLeft.h"
#include "BlasterAIMoveUpDiagRight.h"
#include "BlasterAIMoveUpDiagLeft.h"


// Set up all the unique copies of states
//Centipede
const MoveRightEndDownwards MoveFSM::StateMoveRightEndDownwards;
const MoveRightEndUpwards MoveFSM::StateMoveRightEndUpwards;
const MoveLeftEndDownwards MoveFSM::StateMoveLeftEndDownwards;
const MoveLeftEndUpwards MoveFSM::StateMoveLeftEndUpwards;
const TurnDownSwitchToLeft MoveFSM::StateTurnDownSwitchToLeft;
const TurnDownSwitchToRight MoveFSM::StateTurnDownSwitchToRight;
const TurnUpSwitchToLeft MoveFSM::StateTurnUpSwitchToLeft;
const TurnUpSwitchToRight MoveFSM::StateTurnUpSwitchToRight;
const PoisonedTurnDownEndLeft MoveFSM::StatePoisonedTurnDownEndLeft;
const PoisonedTurnDownEndRight MoveFSM::StatePoisonedTurnDownEndRight;

//Spider
const SpiderMoveDown MoveFSM::StateSpiderMoveDown;
const SpiderMoveUp MoveFSM::StateSpiderMoveUp;
const SpiderMoveDownDiagRight MoveFSM::StateSpiderMoveDownDiagRight;
const SpiderMoveDownDiagLeft MoveFSM::StateSpiderMoveDownDiagLeft;
const SpiderMoveUpDiagLeft MoveFSM::StateSpiderMoveUpDiagLeft;
const SpiderMoveUpDiagRight MoveFSM::StateSpiderMoveUpDiagRight;

//Blaster AI
const BlasterAIMoveDownDiagRight MoveFSM::StateBlasterAIMoveDownDiagRight;
const BlasterAIMoveDownDiagLeft MoveFSM::StateBlasterAIMoveDownDiagLeft;
const BlasterAIMoveUpDiagLeft MoveFSM::StateBlasterAIMoveUpDiagLeft;
const BlasterAIMoveUpDiagRight MoveFSM::StateBlasterAIMoveUpDiagRight;