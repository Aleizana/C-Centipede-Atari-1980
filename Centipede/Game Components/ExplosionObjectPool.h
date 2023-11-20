// ExplosionObjectPool

#ifndef _ExplosionObjectPool
#define _ExplosionObjectPool

#include <stack>
class Explosion;

class ExplosionObjectPool
{
private:
	std::stack<Explosion*> recycledItems;

public:
	ExplosionObjectPool();
	ExplosionObjectPool(const ExplosionObjectPool&) = delete;
	ExplosionObjectPool& operator=(const ExplosionObjectPool&) = delete;
	~ExplosionObjectPool();

	Explosion* GetExplosion();

	void ReturnExplosion(Explosion* b);
};


#endif _ExplosionObjectPool
