#ifndef _MoveStateBase
#define _MoveStateBase

#include "TEAL\CommonElements.h"
#include <stack>

struct OffsetArray;
class CentipedeHead;

class MoveState
{
public:
	MoveState() = default;
	MoveState(MoveState& copyMoveState) = delete;
	MoveState& operator=(MoveState&) = delete;
	~MoveState() = default;

	const OffsetArray* GetMoveOffsets() const { return MyMoveOffsets; }
	virtual const MoveState* GetNextState(CentipedeHead* chead) const = 0;

	//Function to get the next state based off of only row col input
	virtual const MoveState* GetNextState(int row, int col, sf::Vector2f pos) const = 0;

	virtual void Show() const = 0;
	virtual int IncrementRow() const = 0;
	virtual int IncrementCol() const = 0;


	virtual std::stack<int> GetSpriteProperties(const int offsetArrIndex) const = 0;


protected:
	const OffsetArray* MyMoveOffsets = nullptr;


};

#endif 