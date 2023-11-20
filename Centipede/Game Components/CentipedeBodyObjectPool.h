// CentipedeBodyObjectPool
// AB 2019

#ifndef _CentipedeBodyObjectPool
#define _CentipedeBodyObjectPool

#include <stack>
class CentipedeBody;

class CentipedeBodyObjectPool
{
private:
	std::stack<CentipedeBody*> recycledItems;

public:
	CentipedeBodyObjectPool();
	CentipedeBodyObjectPool(const CentipedeBodyObjectPool&) = delete;
	CentipedeBodyObjectPool& operator=(const CentipedeBodyObjectPool&) = delete;
	~CentipedeBodyObjectPool();

	CentipedeBody* GetCentipedeBody();

	void ReturnCentipedeBody(CentipedeBody* b);
};


#endif _CentipedeBodyObjectPool
