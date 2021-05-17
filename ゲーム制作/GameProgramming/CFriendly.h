#ifndef FRIENDLY_H
#define FRIENDLY_H
#include"CCharacter.h"
#include"CCollider.h"
class CFriendly :public CCharacter{
public:
	CFriendly(CModel*model, CVector position, CVector rotation, CVector scale);
	void Update();
	//ƒRƒ‰ƒCƒ_
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;

	void Collision(CCollider*m, CCollider*o);
	void TaskCollision();
};
#endif