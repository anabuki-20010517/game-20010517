#include"CMaterial.h"
#include<string.h>
#include"glut.h"
CMaterial::CMaterial()
:mVertexNum(0)
{
	memset(mName, 0, sizeof(mName));
	memset(mDiffuse, 0, sizeof(mDiffuse));

}
void CMaterial::Enabled(){
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	if (mTexture.mId)
	{
		//テクスチャを使用可能にする
		glEnable(GL_TEXTURE_2D);
		//テクスチャをバインド
		glBindTexture(GL_TEXTURE_2D, mTexture.mId);
		//あるふぁぬ連弩を有効に
		glEnable(GL_BLEND);
		//ブレンド方法を指定
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}
//マテリアルを無効にする
void CMaterial::Disabled(){

	if (mTexture.mId)
	{
		//アルファブレンドを無効
		glDisable(GL_BLEND);
		//テクスチャのバインドを解く
		glBindTexture(GL_TEXTURE_2D, 0);
		//テクスチャ無効
		glDisable(GL_TEXTURE_2D);
	}
}
