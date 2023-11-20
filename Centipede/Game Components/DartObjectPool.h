// DartObjectPool
// AB 2019

#ifndef _DartObjectPool
#define _DartObjectPool

#include <stack>
class Dart;

class DartObjectPool
{
private:
	std::stack<Dart*> recycledItems;

public:
	DartObjectPool();
	DartObjectPool(const DartObjectPool&) = delete;
	DartObjectPool& operator=(const DartObjectPool&) = delete;
	~DartObjectPool();

	Dart* GetDart();

	void ReturnDart(Dart* b);
};


#endif _DartObjectPool
