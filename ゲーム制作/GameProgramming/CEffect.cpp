#include"CEffect.h"

CMaterial CEffect::sMaterial;
CEffect::CEffect(const CVector &pos, float w, float h, char*texture, int row , int col , int fps )
:CBillBoard(pos, w, h), mRows(row), mCols(col), mFps(fps), mFrame(0){
	if (sMaterial.mTexture.mId == 0)
	{
		sMaterial.mTexture.Load(texture);
		sMaterial.mDiffuse[0] = sMaterial.mDiffuse[1] =
			sMaterial.mDiffuse[2] = sMaterial.mDiffuse[3] = 1.0f;
	}
}
void CEffect::Update(){
	int frame = mFrame++ / mFps;
	frame %= (mRows*mCols);
	float left = 1.0f / mCols*(frame%mCols);
	float righ = left + 1.0f / mCols;
	float top = 1.0f - 1.0f / mRows*(frame / mCols);
	float bot = top - 1.0f / mRows;
	mT[0].mUv[0] = CVector(righ, top, 0.0f);
	mT[0].mUv[1] = CVector(left, bot, 0.0f);
	mT[0].mUv[2] = CVector(righ, bot, 0.0f);
	mT[1].mUv[0] = CVector(left, top, 0.0f);
	mT[1].mUv[1] = CVector(left, bot, 0.0f);
	mT[1].mUv[2] = CVector(righ, top, 0.0f);
	CBillBoard::Update();
	if (frame == mRows*mCols - 1){
		mEnabled = false;
	}
}

void CEffect::Render(){
	glDisable(GL_DEPTH_TEST);
	CBillBoard::Render(&sMaterial);
	glEnable(GL_DEPTH_TEST);
}