#ifndef _CentiHead
#define _CentiHead

#include "TEAL\CommonElements.h"
#include "CentipedeBase.h"

//Foward declare for reference to CentipedeHeadMover class
class Dart;
class Blaster;
class MoveState;
class CentipedeBody;

class CentipedeHead : public CentipedeBase
{
public:
	CentipedeHead();
	CentipedeHead(const CentipedeHead& copyHead) = delete;
	CentipedeHead& operator=(const CentipedeHead&) = delete;
	~CentipedeHead() = default;

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision(GameObject* other) {};

	virtual void Collision(Dart* other);

	void Initialize(sf::Vector2f p, int row, int col, const MoveState* setState, CentipedeBody* firstNode, int offsetIncr, float speed);

	//For the head move to receive the pos of and set the pos of the centipede head
	sf::Vector2f GetHeadPos();
	void SetHeadPos(sf::Vector2f newPos);

	//Getters and setters for the row and col of the head, accessed by the HeadMover
	int GetHeadRow();
	int GetHeadCol();
	void SetHeadRow(int newRow);
	void SetHeadCol(int newCol);

	void SetBodyNodePtr(CentipedeBody* _firstBody);
	CentipedeBody* GetBodyNodePtr();

	//To manually queue a movement state for the centipede head
	virtual void SetMoveState_FSM(const MoveState* newState);

	//To set the move increment value of the head
	void SetMoveIncrement(int newVal);


private:
	//Pointer to the start of the linked-list of bodies
	CentipedeBody* bodyFirstNode;

	virtual void privCreateMushroomFromBody();

	virtual void privOnDeathCreateHead();

	virtual void UpdateSpriteValuesFromState();
};

#endif