#include"CTransform.h"

void CTransform::Update(){
	mMatrixScale.Scale(mScale.mX, mScale.mY, mScale.mZ);
	mMatrixRotate =
		CMatrix().RotateZ(mRotation.mZ)*
		CMatrix().RotateX(mRotation.mX)*
		CMatrix().RotateY(mRotation.mY);
		mMatrixTranslate.Translate(mPosition.mX, mPosition.mY, mPosition.mZ);
	mMatrix = mMatrixScale*mMatrixRotate*mMatrixTranslate;
}