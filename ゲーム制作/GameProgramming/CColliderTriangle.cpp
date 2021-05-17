#include"CColliderTriangle.h"
#include "CCollisionManager.h"

CColliderTriangle::CColliderTriangle(CCharacter*parent, CMatrix*matrix, 
	const CVector &v0, const CVector &v1, const CVector &v2)
{
	Set(parent, matrix, v0, v1, v2);
}
void CColliderTriangle::Set(CCharacter*parent, CMatrix*matrix, 
	const CVector &v0, const CVector &v1, const CVector &v2)
{
	mType = ETRIANGLE;
	mpParent = parent;
	if (matrix)
		mpMatrix = matrix;
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}
void CColliderTriangle::Render()
{
	glPushMatrix();
	glMultMatrixf(mpMatrix->mM[0]);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	float c[] = { 1.0f, 0.0f, 0.0f, 0.2f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	glBegin(GL_TRIANGLES);
	glVertex3f(mV[0].mX, mV[0].mY, mV[0].mZ);
	glVertex3f(mV[1].mX, mV[1].mY, mV[1].mZ);
	glVertex3f(mV[2].mX, mV[2].mY, mV[2].mZ);
	glEnd();

	glEnable(GL_LIGHTING);
	glDisable(GL_ALPHA);
	glPopMatrix();
}
void CColliderTriangle::ChangePriority()
{
	CVector pos = (mV[0] * *mpMatrix + mV[1] * *mpMatrix + mV[2] * *mpMatrix)*(1.0f / 3.0f);
	mPriority = pos.Length();
	CCollisionManager::Get()->Remove(this);
	CCollisionManager::Get()->Add(this);
}