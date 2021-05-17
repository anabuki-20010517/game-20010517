#include"CColliderLine.h"
#include"CCollisionManager.h"
CColliderLine::CColliderLine(CCharacter*parent, CMatrix*matrix, const CVector&v0, const CVector&v1)
{
	Set(parent, matrix, v0, v1);
}
void CColliderLine::Set(CCharacter*parent, CMatrix*matrix, const CVector&v0, const CVector&v1)
{
	mType = ELINE;
	mpParent = parent;
	if (matrix)
		mpMatrix = matrix;
	mV[0] = v0;
	mV[1] = v1;
}
void CColliderLine::Render()
{
	glPushMatrix();
	glMultMatrixf(mpMatrix->mM[0]);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);

	float c[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	glBegin(GL_LINES);
	glVertex3f(mV[0].mX, mV[0].mY, mV[0].mZ);
	glVertex3f(mV[1].mX, mV[1].mY, mV[1].mZ);
	glEnd();

	glEnable(GL_LIGHTING);
	glDisable(GL_ALPHA);
	glPopMatrix();
}
void CColliderLine::ChangePriority()
{
	CVector pos = (mV[0] * *mpMatrix + mV[1] * *mpMatrix)*(0.5f);
	mPriority = pos.Length();
	CCollisionManager::Get()->Remove(this);
	CCollisionManager::Get()->Add(this);
}