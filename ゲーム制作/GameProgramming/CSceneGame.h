#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include"CVector.h"
#include"CModel.h"
#include"CCharacter.h"
#include"CPlayer.h"
#include"CColliderTriangle.h"
#include"CColliderMesh.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
public:
	CModel mModel;
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	CVector mEye;
	CModel mBackGround;
	CPlayer mPlayer;
	
	CColliderTriangle mColliderTriangle;
	CColliderTriangle mColliderTriangle2;
	CColliderMesh mColliderMesh;
	CMatrix mBackGroundMatrix;
};


#endif
