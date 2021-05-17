#include "CSceneGame.h"
#include"glut.h"
#include"CVector.h"
#include"CTriangle.h"
#include"CKey.h"
#include"CMatrix.h"
#include"CTransform.h"
#include"CTaskManager.h"
#include"CEnemy.h"
#include"CCollisionManager.h"
#include"CBillBoard.h"
#include"CCamera.h"
CModel mModelC5;
#include"CEnemy2.h"
#include"CFriendly.h"


void CSceneGame::Init() {
	mEye = CVector(1.0f, 2.0f, 3.0f);
	mModel.Load("f14.obj", "f14.mtl"); 
	mBackGround.Load("sky.obj", "sky.mtl");
	CMatrix matrix;
	matrix.Print();

	mPlayer.mpModel = &mModel;
	mPlayer.mPosition = CVector(0.0f, 0.0f, -3.0f)*mBackGroundMatrix;
	mPlayer.mRotation = CVector(0.0f, 180.0f, 0.0f);
	mPlayer.mScale = CVector(0.1f, 0.1f, 0.1f);

	mModelC5.Load("c5.obj", "c5.mtl");
	new CEnemy(&mModelC5, CVector(0.0f, 10.0f, -100.0f)
		*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	new CEnemy(&mModelC5, CVector(30.0f,10.0f, -130.0f)
		*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);

	mColliderTriangle.Set(NULL, NULL
		, CVector(-50.0f, 0.0f, -50.0f)
		, CVector(-50.0f, 0.0f, 50.0f)
		, CVector(50.0f, 0.0f, -50.0f));

	mColliderTriangle2.Set(NULL, NULL
		, CVector(-50.0f, 0.0f, 50.0f)
		, CVector(50.0f, 0.0f, 50.0f)
		, CVector(50.0f, 0.0f, -50.0f));

	mColliderMesh.Set(NULL, &mBackGroundMatrix, &mBackGround);
	new CEnemy2(CVector(-5.0f, 1.0f, -10.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	new CEnemy2(CVector(5.0f, 1.0f, -10.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	mBackGroundMatrix.Translate(0.0f, 0.0f, -500.0f);

}


void CSceneGame::Update() {
	CTaskManager::Get()->Update();
	//削除CCollisionManager::Get()->Collision();
	CTaskManager::Get()->TaskCollision();
	CVector v0,v1,v2,n;
	n.mX = 0.0f; n.mY = 1.0f; n.mZ = 0.0f;
	v0.mX = 0.0f; v0.mY = 0.0f; v0.mZ = 0.5f;
	v1.mX = 1.0f; v1.mY = 0.0f; v1.mZ = 0.0f;
	v2.mX = 0.0f; v2.mY = 0.0f; v2.mZ = -0.5f;

	
	//視点の設定
	CVector e, c, u;
	//視点を求める
	e = CVector(-2.0f, 10.0f, -30.0f)*mPlayer.mMatrix;	//注視点を求める
	c = mPlayer.mPosition;
	//カメラの設定
	u = CVector(0, 1, 0)*mPlayer.mMatrixRotate;
	//gluLookAt(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
	Camera.Set(e, c, u);
	Camera.Render();
	mBackGround.Render();

	if (CKey::Push('J'))
	{
		mEye.mX -= 0.1f;
	}
	if (CKey::Push('L'))
	{
		mEye.mX += 0.1f;
	}
	if (CKey::Push('I'))
	{
		mEye.mZ -= 0.1f;
	}
	if (CKey::Push('K'))
	{
		mEye.mZ += 0.1f;
	}
	if (CKey::Push('O'))
	{
		mEye.mY -= 0.1f;
	}
	if (CKey::Push('M'))
	{
		mEye.mY += 0.1f;
	}

	CTaskManager::Get()->Delete();
	CTaskManager::Get()->Render();
    CCollisionManager::Get()->Render();

	mBackGround.Render(mBackGroundMatrix);
}
