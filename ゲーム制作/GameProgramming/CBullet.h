#ifndef CBULLET_H
#define CBULLET_H
#include"CCharacter.h"
#include"CTriangle.h"
#include"CCollider.h"
class CBullet :public CCharacter{
public:
	CTriangle mT;
	void Set(float w, float d);
	void Update();
	void Render();
	int mLife;
	CBullet();

	CCollider mCollider;
	//Õ“Ëˆ—
	void Collision(CCollider*m, CCollider*o);
	void TaskCollision();
};

#endif