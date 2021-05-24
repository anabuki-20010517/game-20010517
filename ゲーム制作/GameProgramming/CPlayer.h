#ifndef CPLAYER_H
#define CPLAYER_H
#include"CCharacter.h"
#include"CBullet.h"
#include"CColliderLine.h"
#include"CText.h"
#include"CUtil.h"

class CPlayer :public CCharacter{
public:
	void Update();
	CColliderLine mLine;
	CColliderLine mLine2;
	CColliderLine mLine3;
	CPlayer();
	void Collision(CCollider*m, CCollider*o);
	void TaskCollision();
	CText mText;
	void Render();
	CCollider mCollider;
	CMatrix mBackGroundMatrix;
};
#endif