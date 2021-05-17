#ifndef CCOLLIDERLINE_H
#define CCOLLIDERLINE_H
#include"CCollider.h"
class CColliderLine :public CCollider
{
public:
	CColliderLine(){}
	CColliderLine(CCharacter*parent, CMatrix*matrix, const CVector&v0, const CVector&v1);
	void Set(CCharacter*parent, CMatrix*matrix, const CVector&v0, const CVector&v1);
	void Render();
	void ChangePriority();
};
#endif