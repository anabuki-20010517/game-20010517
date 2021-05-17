#ifndef CCOLLIDERTRIANGLE_H
#define CCOLLIDERTRIANGLE_H
#include"CCollider.h"
class CColliderTriangle:public CCollider
{
public:
	CColliderTriangle(){}
	CColliderTriangle(CCharacter*parent, CMatrix*matrix
	, const CVector &v0, const CVector &v1, const CVector &v2);
	void Set(CCharacter*parent, CMatrix*matrix
		, const CVector &v0, const CVector &v1, const CVector &v2);
	void Render();
	void ChangePriority();
};

#endif