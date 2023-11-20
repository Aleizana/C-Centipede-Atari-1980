// SpiderObjectPool
// AB 2019

#ifndef _SpiderObjectPool
#define _SpiderObjectPool

#include <stack>
class Spider;

class SpiderObjectPool
{
private:
	std::stack<Spider*> recycledItems;

public:
	SpiderObjectPool();
	SpiderObjectPool(const SpiderObjectPool&) = delete;
	SpiderObjectPool& operator=(const SpiderObjectPool&) = delete;
	~SpiderObjectPool();

	Spider* GetSpider();

	void ReturnSpider(Spider* b);
};


#endif _SpiderObjectPool
