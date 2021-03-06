#include"CPlayer.h"
#include"CKey.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"
#include"CEnemy.h"
#include"CFriendly.h"
CModel mModelC;
#define OBJ "f16.obj"
#define MTL "f16.mtl"
CPlayer* CPlayer::spInstance = 0;

CPlayer::CPlayer()
: mLine(this, &mMatrix, CVector(0.0f, 0.0f, -14.0f), CVector(0.0f, 0.0f, 17.0f))
, mLine2(this, &mMatrix, CVector(0.0f, 5.0f, -8.0f), CVector(0.0f, -3.0f, -8.0f))
, mLine3(this, &mMatrix, CVector(9.0f, 0.0f, -8.0f), CVector(-9.0f, 0.0f, -8.0f))
, mCollider(this, &mMatrix, CVector(0.0f,0.0f,0.0f),0.5f)
, mStart(1)
, mStop(0)
{
	mText.LoadTexture("FontWhite.tga", 1, 64);
	mTag = EPLAYER;
	mFriend = 10;
	spInstance = this;
}

void CPlayer::Update(){
	mStop--;
	if (CKey::Push('A')){
		mRotation.mY += 1;
	}
	if (CKey::Push('D')){
		mRotation.mY -= 1;
	}
	if (CKey::Push(VK_UP)){
		//Z軸方向に1進んだ値を回転移動させる
		mPosition = CVector(0.0f, 0.0f, 3.0f)*mMatrix;
	}
	if (CKey::Push('S')){
		mRotation.mX -= 1;
	}
	if (CKey::Push('W')){
		mRotation.mX += 1;
	}
	if (CKey::Push(VK_SPACE)){
		CBullet*bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->mPosition = CVector(0.0f, 0.0f, 10.0f)*mMatrix;
		bullet->mRotation = mRotation;
		bullet->Update();
		//TaskManager.Add(bullet);
	}
	if (mStop<0){
		if (mFriend > 0){
			if (CKey::Push('Z')){
				mModelC.Load(OBJ, MTL);
				new CFriendly(CVector(0.0f, 0.0f, 30.0f)*mMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
				mFriend--;
				mStop = 100;
			}
		}
	}
	if (mStart > 0){
		if (CKey::Push('R')){
			mStart--;
		}
	}
	CTransform::Update();
}
void CPlayer::Collision(CCollider*m, CCollider*o){
	switch (m->mType){
	case CCollider::ELINE:
		if (o->mType == CCollider::ETRIANGLE){
			CVector adjust;
			CCollider::CollisonTriangleLine(o, m, &adjust);
			mPosition = mPosition - adjust*-1;
			CTransform::Update();
		}
		break;
	}
}
void CPlayer::TaskCollision()
{
	
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	//衝突処理の実行
	CCollisionManager::Get()->Collision(&mLine, COLLSIONRANGE);
	CCollisionManager::Get()->Collision(&mLine2, COLLSIONRANGE);
	CCollisionManager::Get()->Collision(&mLine3, COLLSIONRANGE);
	mCollider.ChangePriority();
}
void CPlayer::Render()
{
	CCharacter::Render();
	CUtil::Start2D(-400, 400, -300, 300);
	glColor4f(0.0f, 1.0f,0.0f, 0.4f);
	char buf[64];

	sprintf(buf, "PY:%7.2f", mPosition.mY);
	mText.DrawString(buf, 100, 30, 8, 16);
	sprintf(buf, "RX:%7.2f", mRotation.mX);
	mText.DrawString(buf, 100, 0, 8, 16);
	sprintf(buf, "RY:%7.2f", mRotation.mY);
	mText.DrawString(buf, 100, -100, 8, 16);

	CUtil::End2D();
}