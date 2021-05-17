#ifndef CENEMY2_H
#define CENEMY2_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CTaskManager.h"
class CEnemy2 :public CCharacter{
public:
	static CModel mModel;
	CCollider mCollider;
	CEnemy2();
	CEnemy2(const CVector&position, const CVector&rotation, const CVector&scale);
	void Update();
	void Collision(CCollider*m, CCollider*o);
	void TaskCollision();
	CCollider mColSearch;
	CCharacter*mpPlayer;//プレイヤーのポインタ
	int mHp;
};
#endif