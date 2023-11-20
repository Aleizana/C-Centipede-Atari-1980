// FleaObjectPool
// AB 2019

#ifndef _FleaObjectPool
#define _FleaObjectPool

#include <stack>
class Flea;

class FleaObjectPool
{
private:
	std::stack<Flea*> recycledItems;

public:
	FleaObjectPool();
	FleaObjectPool(const FleaObjectPool&) = delete;
	FleaObjectPool& operator=(const FleaObjectPool&) = delete;
	~FleaObjectPool();

	Flea* GetFlea();

	void ReturnFlea(Flea* b);
};


#endif _FleaObjectPool
