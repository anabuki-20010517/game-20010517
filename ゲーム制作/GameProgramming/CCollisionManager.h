#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H
#define COLLSIONRANGE 30
#include"CTaskManager.h"
#include"CCollider.h"
class CCollisionManager :public CTaskManager
{
	static CCollisionManager*mpInstance;
public:
	static CCollisionManager*Get(); 
	void Collision();
	void Collision(CCollider*c, int range);
};
#endif