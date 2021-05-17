#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H
#include"CModel.h"
#include"CColliderTriangle.h"

class CColliderMesh
{
public:
	CColliderTriangle*mpColliderTriangles;
	CColliderMesh();
	~CColliderMesh();
	void Set(CCharacter*parent, CMatrix*matrix, CModel*model);
};
#endif