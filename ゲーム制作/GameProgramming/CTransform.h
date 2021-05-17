#ifndef CTRANSFORM_H
#define CTRANSFORM_H
#include"CVector.h"
class CTransform{
public:
	CVector mPosition; //ˆÊ’u
	CVector mRotation; //‰ñ“]
	CVector mScale; //Šg‘åk¬
	CMatrix mMatrixTranslate; //•½sˆÚ“®s—ñ
	CMatrix mMatrixRotate; //‰ñ“]s—ñ
	CMatrix mMatrixScale; //Šg‘åk¬s—ñ
	CMatrix mMatrix; //‡¬s—ñ
	void Update();
};
#endif