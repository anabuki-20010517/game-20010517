#ifndef CMATRIX_H
#define CMATRIX_H
class CMatrix{
public:
	float mM[4][4];
	void Print();
	CMatrix();
	CMatrix Identity();
	CMatrix Scale(float sx, float sy, float sz);
	CMatrix RotateY(float degree);
	CMatrix RotateZ(float degree);
	CMatrix RotateX(float degree);
	CMatrix Translate(float mx, float my, float mz);
	CMatrix operator*(const CMatrix &m);
};

#endif