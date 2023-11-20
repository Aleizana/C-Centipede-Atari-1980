#ifndef _CentiBody
#define _CentiBody

#include "TEAL\CommonElements.h"
#include "CentipedeBase.h"

//Foward declare for reference to CentipedeBodyMover class
class Dart;
class Blaster;
class MoveState;
class CentipedeHead;

class CentipedeBody : public CentipedeBase
{
public:
	CentipedeBody();
	CentipedeBody(const CentipedeBody& copyBody) = delete;
	CentipedeBody& operator=(const CentipedeBody&) = delete;
	~CentipedeBody() = default;

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision(GameObject* other) {};

	virtual void Collision(Dart* other);

	void Initialize(sf::Vector2f p, int row, int col, CentipedeBody* _nextBody, CentipedeBody* _prevBody, CentipedeHead* _head, float speed);

	//For the Body move to receive the pos of and set the pos of the centipede Body
	sf::Vector2f GetBodyPos();
	void SetBodyPos(sf::Vector2f newPos);

	//Getters and setters for the row and col of the Body, accessed by the BodyMover
	int GetBodyRow();
	int GetBodyCol();
	void SetBodyRow(int newRow);
	void SetBodyCol(int newCol);

	//Getter and setter for the next/prev ptrs of a node
	void SetNextPtr(CentipedeBody* _nextPtr);
	void SetPrevPtr(CentipedeBody* _prevPtr);
	CentipedeBody* GetNextPtr();
	CentipedeBody* GetPrevPtr();

	//For the previous node in the list to send move state updates to this node
	virtual void SetMoveState_FSM(const MoveState* newState);
	const MoveState* GetMyMoveState();

	//Returns the array incrementor amount
	int GetArrIncVal();

	//Changes the head ptrs in the linked list starting from the current node
	void UpdateBodyData(CentipedeHead* headRef, const MoveState* newState);

private:
	//Pointer to the next node, behind this one, of the linked-list of bodies
	CentipedeBody* bodyNextNode;

	//Pointer to the previous node, in front of this one, of the linked-list of bodies
	CentipedeBody* bodyPrevNode;

	//Pointer to the head of the entire centipede
	CentipedeHead* headNode;

	//Private function to update the row and column of the body locally
	void privUpdateMyRowCol();

	//Private function to handle the splitting of the centipede, and creation of a new head, when a body part collides with the dart
	virtual void privOnDeathCreateHead();

	void privUpdateBodyData(CentipedeHead* _newHead, const MoveState* newState);

	virtual void privCreateMushroomFromBody();

	virtual void UpdateSpriteValuesFromState();
};

#endif