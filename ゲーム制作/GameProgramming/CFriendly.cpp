#include"CFriendly.h"
#include"CEffect.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"
#include"CBullet.h"
#include"CPlayer.h"
#define OBJ "f16.obj"
#define MTL "f16.mtl"
#define HP 3
CModel CFriendly::mModel;
CFriendly* CFriendly::spInstance = 0;
CFriendly::CFriendly()
:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4f)
, mColSearch(this, &mMatrix, CVector(0.0f, 0.0f, 100.0f), 30.0f)
, mpPlayer(0)
, mHp(HP)
, mCount(0)
{
	if (mModel.mTriangles.size() == 0)
	{
		mModel.Load(OBJ, MTL);
	}
	mpModel = &mModel;
	mColSearch.mTag = CCollider::ESEARCH;
	mTag = EFRIENDLY;
	spInstance = this;
}

CFriendly::CFriendly(const CVector&position, const CVector&rotation,
	const CVector&scale)
	: CFriendly()
{
	mPosition = position; //位置
	mRotation = rotation; //回転
	mScale = scale;		  //拡縮
	CTransform::Update(); //行列
	mPriority = 1;
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);

}
void CFriendly::Update(){
	mCount--;
	CVector vx = CVector(1.0f, 0.0f, 0.0f)*mMatrixRotate;
	CVector vy = CVector(0.0f, 1.0f, 0.0f)*mMatrixRotate;
	CVector vz = CVector(0.0f, 0.0f, 1.0f)*mMatrixRotate;
	if (CPlayer::spInstance->mStart == 0)
	{
		if (mpPlayer)
		{
			CVector vp = mpPlayer->mPosition - mPosition;
			float dx = vp.Dot(vx);
			float dy = vp.Dot(vy);
			float dz = vp.Dot(vz);

			if (dx > 0.0f)
			{
				mRotation.mY++;
			}
			else{
				mRotation.mY--;
			}
			if (dy > 0.0f)
			{
				mRotation.mX--;
			}
			else{
				mRotation.mX++;
			}
			//X軸のズレが2.0以下
			if (-2.0f < dx && dx < 2.0f)
			{
				//Y軸のズレが2.0以下
				if (-2.0f < dy && dy < 2.0f)
				{
					if (0.0f < dz){
						if (mCount < 0){
							CBullet*bullet = new CBullet();
							bullet->Set(0.1f, 1.5f);
							bullet->mPosition = CVector(0.0f, 0.0f, 10.0f)*mMatrix;
							bullet->mRotation = mRotation;
							bullet->Update();
							mCount = 25;
						}
					}
				}
			}
		}
		mpPlayer = 0;
		if (mHp <= 0)
		{
			mHp--;
			//15フレーム毎にエフェクト
			if (mHp % 15 == 0)
			{
				new CEffect(mPosition, 1.0f, 1.0f, "exp.tag", 4, 4, 2);
			}
			mPosition.mY -= 0.03f;
			CTransform::Update();
			return;
		}
		CTransform::Update();
		//mPosition = CVector(0.0f, 0.0f, 0.9f)*mMatrix;
	}
}

void CFriendly::Collision(CCollider*m, CCollider*o){
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}
	if (m->mTag == CCollider::ESEARCH)
	{
		if (o->mType == CCollider::ESPHERE)
		{
			if (o->mpParent->mTag == EENEMY)
			{

				if (CCollider::Collision(m, o))
				{
					mpPlayer = o->mpParent;
				}
			}
		}
		return;
	}
	switch (o->mType)
	{
	case CCollider::ESPHERE:
		if (CCollider::Collision(m, o)){

				new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
				mHp--;
			}
	
			break;
	
	case CCollider::ETRIANGLE:
		CVector adjust;
		if (CCollider::CollidionTriangleSphere(o, m, &adjust))
		{
			mPosition = mPosition + adjust;
			if (mHp <= 0)
			{
				mEnabled = false;
			}
		}
		break;
	}
}
void CFriendly::TaskCollision()
{
	mCollider.ChangePriority();

	//衝突処理の実行
	CCollisionManager::Get()->Collision(&mCollider, COLLSIONRANGE);
	mColSearch.ChangePriority();
	CCollisionManager::Get()->Collision(&mColSearch, COLLSIONRANGE); 
}