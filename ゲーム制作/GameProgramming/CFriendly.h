#ifndef CFRIENDLY_H
#define CFRIENDLY_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CTaskManager.h"
class CFriendly :public CCharacter{
public:
	static CModel mModel;
	CCollider mCollider;
	CFriendly();
	CFriendly(const CVector&position, const CVector&rotation, const CVector&scale);
	void Update();
	void Collision(CCollider*m, CCollider*o);
	void TaskCollision();
	CCollider mColSearch;
	CCharacter*mpPlayer;//プレイヤーのポインタ
	int mHp;
	int mCount;
};
#endif