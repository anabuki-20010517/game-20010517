#ifndef CCOLLIDER_H
#define CCOLLIDER_H
#include"CCharacter.h"
#include"CTransform.h"
class CCollider :public CTransform,public CTask{
public:
	CCharacter*mpParent;//	親
	CMatrix*mpMatrix;//親行列
	float mRadius;//半径
	CCollider(CCharacter*parent, CMatrix*matrix, CVector position, float radius);
	void Render();
	~CCollider();
	//衝突判定
	static bool Collision(CCollider*m, CCollider*o);
	enum EType{
		ESPHERE,
		ETRIANGLE,
		ELINE,
	};
	EType mType;
	CVector mV[3];
	CCollider();
	//CollisionTriangleLine(三角コライダ、線分コライダ、調整値）
	//調整値：衝突してない位置まで戻す
	static bool CollisonTriangleLine(CCollider*triangle, CCollider*line, CVector*abjust);
	static bool CollidionTriangleSphere(CCollider*triangle, CCollider*sphere, CVector*adjust);
	void ChangePriority();

	enum ETag
	{
		EBODY,
		ESEARCH,
	};
	ETag mTag;
};

#endif