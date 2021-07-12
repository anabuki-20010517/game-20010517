#ifndef COVER_H
#define COVER_H
#include"CCharacter.h"
#include"CCollider.h"
class COver:CCharacter{
public:
	static CModel mModel;
	CCollider mCollider;
	COver();
	COver(const CVector&position, const CVector&rotation, const CVector&scale);
	void Update();
	void Collision(CCollider*m, CCollider*o);
	void TaskCollision();
	CCollider mColSearch;
	CCharacter*mpPlayer;//プレイヤーのポインタ
	int mHp;
};

#endif