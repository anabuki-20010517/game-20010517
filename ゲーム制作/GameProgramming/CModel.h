#ifndef CMODEL_H
#define CMODEL_H
#include <vector>
#include"CTriangle.h"
#include"string.h"
#include"CVector.h"
#include"CMaterial.h"
class CModel{
public:
	void Load(char*obj, char*mtl);
	std::vector<CTriangle> mTriangles;
	std::vector<CMaterial*>mpMaterials;
	void Render();
	~CModel();
	void Render(const CMatrix &m);
	float*mpVertex;//頂点座標
	float*mpNormal;//法線
	float*mpTextureCoord;//テクスチャマッピング
	CModel();
};
#endif