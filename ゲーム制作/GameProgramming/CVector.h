#ifndef CVECTOR_H
#define CVECTOR_H
#include "CMatrix.h"


class CVector{
public:
	CVector();
	CVector(float x, float y, float z);
	float mX, mY, mZ;
	//各軸の値設定
	void Set(float x, float y, float z);
	CVector operator*(const CMatrix &m);
	//演算子のオーバーロード
	CVector operator-(const CVector &v);
	//ベクトルの長さを返す
	float Length();
	float Dot(const CVector &v);
	CVector Cross(const CVector &v);
	CVector operator*(const float &f);
	CVector CVector::Normalize();
	CVector operator+(const CVector &v);
};

#endif