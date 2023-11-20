// CentipedeHeadMoverObjectPool
// AB 2019

#ifndef _CentipedeHeadMoverObjectPool
#define _CentipedeHeadMoverObjectPool

#include <stack>
class CentipedeHeadMover;

class CentipedeHeadMoverObjectPool
{
private:
	std::stack<CentipedeHeadMover*> recycledItems;

public:
	CentipedeHeadMoverObjectPool();
	CentipedeHeadMoverObjectPool(const CentipedeHeadMoverObjectPool&) = delete;
	CentipedeHeadMoverObjectPool& operator=(const CentipedeHeadMoverObjectPool&) = delete;
	~CentipedeHeadMoverObjectPool();

	CentipedeHeadMover* GetCentipedeHeadMover();

	void ReturnCentipedeHeadMover(CentipedeHeadMover* b);
};


#endif _CentipedeHeadMoverObjectPool

