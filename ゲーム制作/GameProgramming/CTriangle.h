#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include"CVector.h"
class CTriangle{
	public:
		CVector mV[3];
		CVector mN[3];//法線
		void SetVertex(const CVector &v0, const CVector &v1, const CVector &v2);
		void SetNormal(const CVector &vn);
		void SetNormal(const CVector &v0, const CVector &v1, const CVector &v2);
		void Render();
		int mMaterialIdx;	//マテリアル番号
	    CVector mUv[3];		//テクスチャマッピング
		void Render(const CMatrix &m);
		};

#endif