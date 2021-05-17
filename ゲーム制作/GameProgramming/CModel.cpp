#include "CModel.h"
#include<stdio.h>
#include"CVector.h"
CModel::CModel()
:mpVertex(0), mpNormal(0), mpTextureCoord(0)
{

}
void CModel::Load(char*obj, char*mtl){
	//頂点データの保存
	std::vector<CVector>vertex;
	//法線データの保存
	std::vector<CVector>normal;
	//テクスチャマッピングの保存
	std::vector<CVector>uv;

	FILE*fp;
	fp = fopen(mtl, "r");
	if (fp == NULL){
		printf("%s file open error\n", obj);
		return;
	}

	char buf[256];
	//マテリアインデックス
	int idx = 0;
	while (fgets(buf, sizeof(buf), fp) != NULL){
		char str[4][64] = { "", "", "", "" };
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		if (strcmp(str[0], "newmtl") == 0){
			CMaterial*pm = new CMaterial();
			strncpy(pm->mName, str[1], sizeof(pm->mName) - 1);
			mpMaterials.push_back(pm);
			idx = mpMaterials.size() - 1;
		}
		else if (strcmp(str[0], "Kd") == 0){
			mpMaterials[idx]->mDiffuse[0] = atof(str[1]);
			mpMaterials[idx]->mDiffuse[1] = atof(str[2]);
			mpMaterials[idx]->mDiffuse[2] = atof(str[3]);
		}
		else if (strcmp(str[0], "d") == 0){
			mpMaterials[idx]->mDiffuse[3] = atof(str[1]);
		}
		else if (strcmp(str[0], "map_Kd") == 0){
			mpMaterials[idx]->mTexture.Load(str[1]);
		}
	}
	printf("\n");
	fclose(fp);




	fp = fopen(obj, "r");
	if (fp == NULL){
		printf("%s file open error\n", obj);
		return;
	}

	while (fgets(buf, sizeof(buf), fp) != NULL){
		//データを分割
		char str[4][64] = { "", "", "", "" };
		//文字列からデータ4つ変数に代入
		//sscanf(文字列,変換指定子,変数)
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		//文字列の比較
		//strcmp(文字列1,文字列2)
		//文字列が同じときは0、異なるときは0以外を返す
		//先頭がvの時、頂点をvertexに追加
		if (strcmp(str[0], "v") == 0){
			vertex.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));

		}
		else if (strcmp(str[0], "vn") == 0){
			normal.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		//先頭fの時三角形を作成して追加
		else if (strcmp(str[0], "f") == 0){
			int v[3], n[3];
			if (strstr(str[1], "//")){
				sscanf(str[1], "%d//%d", &v[0], &n[0]);
				sscanf(str[2], "%d//%d", &v[1], &n[1]);
				sscanf(str[3], "%d//%d", &v[2], &n[2]);
				CTriangle t;
				t.SetVertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.SetNormal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]); //法線の追加
				t.mMaterialIdx = idx;
				mTriangles.push_back(t);
			}
			else{
				int u[3];
				sscanf(str[1], "%d/%d/%d", &v[0], &u[0], &n[0]);
				sscanf(str[2], "%d/%d/%d", &v[1], &u[1], &n[1]);
				sscanf(str[3], "%d/%d/%d", &v[2], &u[2], &n[2]);
				CTriangle t;
				t.SetVertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.SetNormal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				//テクスチャマッピングの設定
				t.mUv[0] = uv[u[0] - 1];
				t.mUv[1] = uv[u[1] - 1];
				t.mUv[2] = uv[u[2] - 1];
				t.mMaterialIdx = idx;
				mTriangles.push_back(t);
			}
		}
		else if (strcmp(str[0], "usemtl") == 0){
			for (idx = mpMaterials.size() - 1; idx > 0; idx--){
				if (strcmp(mpMaterials[idx]->mName, str[1]) == 0){
					break;
				}
			}
		}
		else if (strcmp(str[0], "vt") == 0){
			//可変調配列uvに追加
			uv.push_back(CVector(atof(str[1]), atof(str[2]), 0.0));
		}


	}
	fclose(fp);
	//頂点配列の作成
mpVertex = new float[mTriangles.size() * 9];
mpNormal = new float[mTriangles.size() * 9];
mpTextureCoord = new float[mTriangles.size() * 6];

int v = 0, t = 0;
for (int i = 0; i < mpMaterials.size(); i++){
	for (int j = 0; j < mTriangles.size(); j++){
		if (i == mTriangles[j].mMaterialIdx){
			mpVertex[v++] = mTriangles[j].mV[0].mX;
			mpVertex[v++] = mTriangles[j].mV[0].mY;
			mpVertex[v++] = mTriangles[j].mV[0].mZ;
			mpVertex[v++] = mTriangles[j].mV[1].mX;
			mpVertex[v++] = mTriangles[j].mV[1].mY;
			mpVertex[v++] = mTriangles[j].mV[1].mZ;
			mpVertex[v++] = mTriangles[j].mV[2].mX;
			mpVertex[v++] = mTriangles[j].mV[2].mY;
			mpVertex[v++] = mTriangles[j].mV[2].mZ;
			v -= 9;

			mpNormal[v++] = mTriangles[j].mN[0].mX;
			mpNormal[v++] = mTriangles[j].mN[0].mY;
			mpNormal[v++] = mTriangles[j].mN[0].mZ;
			mpNormal[v++] = mTriangles[j].mN[1].mX;
			mpNormal[v++] = mTriangles[j].mN[1].mY;
			mpNormal[v++] = mTriangles[j].mN[1].mZ;
			mpNormal[v++] = mTriangles[j].mN[2].mX;
			mpNormal[v++] = mTriangles[j].mN[2].mY;
			mpNormal[v++] = mTriangles[j].mN[2].mZ;

			mpTextureCoord[t++] = mTriangles[j].mUv[0].mX;
			mpTextureCoord[t++] = mTriangles[j].mUv[0].mY;
			mpTextureCoord[t++] = mTriangles[j].mUv[1].mX;
			mpTextureCoord[t++] = mTriangles[j].mUv[1].mY;
			mpTextureCoord[t++] = mTriangles[j].mUv[2].mX;
			mpTextureCoord[t++] = mTriangles[j].mUv[2].mY;
		}
	}
	mpMaterials[i]->mVertexNum = v / 3;
}
}
void CModel::Render(){
	for (int i = 0; i < mTriangles.size(); i++){
		//マテリアルの適用
		mpMaterials[mTriangles[i].mMaterialIdx]->Enabled();
		//可変長配列に添え字でアクセス
		mTriangles[i].Render();
		mpMaterials[mTriangles[i].mMaterialIdx]->Disabled();
	}
}

void CModel::Render(const CMatrix&m){
	glPushMatrix();
	glMultMatrixf(&m.mM[0][0]);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, mpVertex);
	glNormalPointer(GL_FLOAT, 0, mpNormal);
	glTexCoordPointer(2, GL_FLOAT, 0, mpTextureCoord);

	int first = 0;
	for (int i = 0; i < mpMaterials.size(); i++){
		//マテリアルの適用
		mpMaterials[i]->Enabled();
		glDrawArrays(GL_TRIANGLES, first, mpMaterials[i]->mVertexNum - first);
		mpMaterials[i]->Disabled();
		first = mpMaterials[i]->mVertexNum;
	}
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	return;
}
	CModel:: ~CModel()
	{
		for (int i = 0; i < mpMaterials.size(); i++)
		{
			delete mpMaterials[i];
		}
		if (mpVertex){
			delete[]mpVertex;
		}
		if (mpNormal){
			delete[]mpNormal;
		}
		if (mpTextureCoord){
			delete[]mpTextureCoord;
		}


	}
	