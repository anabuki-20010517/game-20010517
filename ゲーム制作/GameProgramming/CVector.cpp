#include"CVector.h"
#include<math.h>
CVector::CVector()
: mX(0.0f)
, mY(0.0f)
, mZ(0.0f)
{}
CVector::CVector(float x, float y, float z)
: mX(x)
, mY(y)
, mZ(z)
{}
void CVector::Set(float x, float y, float z){
	mX = x; mY = y; mZ = z;
};
CVector CVector::operator*(const CMatrix &m)
{
	return CVector(
		mX*m.mM[0][0] + mY*m.mM[1][0] + mZ*m.mM[2][0] + m.mM[3][0],
		mX*m.mM[0][1] + mY*m.mM[1][1] + mZ*m.mM[2][1] + m.mM[3][1],
		mX*m.mM[0][2] + mY*m.mM[1][2] + mZ*m.mM[2][2] + m.mM[3][2]
		);
}
//CVector-Cvector‚Ì‰‰ŽZŒ‹‰Ê‚ð•Ô‚·
CVector CVector::operator-(const CVector &v){
	return CVector(mX - v.mX, mY - v.mY, mZ - v.mZ);
}
//ƒxƒNƒgƒ‹‚Ì’·‚³‚ð•Ô‚·
float CVector::Length(){
	return sqrtf(mX*mX + mY*mY + mZ*mZ);
}
float CVector::Dot(const CVector &v){
	return mX*v.mX + mY*v.mY + mZ*v.mZ;
}
CVector CVector::Cross(const CVector &v){
	return CVector(mY*v.mZ - mZ*v.mY, mZ*v.mX - mX*v.mZ, mX*v.mY - mY*v.mX);
}
CVector CVector::operator*(const float &f){
	return CVector(mX*f,mY*f,mZ*f);


}

CVector CVector::Normalize(){
	return*this*(1.0f / Length());
}
CVector CVector::operator+(const CVector &v){
	return CVector(mX + v.mX, mY + v.mY, mZ + v.mZ);
}