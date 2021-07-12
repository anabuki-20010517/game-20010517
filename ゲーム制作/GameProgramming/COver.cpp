#include"COver.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"
#include"CFriendly.h"
#define OBJ "f16.obj"
#define MTL "f16.mtl"
#define HP 2
CModel COver::mModel;

COver::COver()
: mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4f)
, mColSearch(this, &mMatrix, CVector(0.0f, 0.0f, 30.0f), 30.0f)

{
	if (mModel.mTriangles.size() == 0)
	{
		mModel.Load(OBJ, MTL);
	}
	mpModel = &mModel;
	mColSearch.mTag = CCollider::ESEARCH;
	mTag = EOVER;
}

COver::COver(const CVector&position, const CVector&rotation,
	const CVector&scale)
	: COver()
{
	mPosition = position; //ˆÊ’u
	mRotation = rotation; //‰ñ“]
	mScale = scale;		  //Šgk
	CTransform::Update(); //s—ñ
	mPriority = 1;
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);

}
void COver::Update(){
	CVector vx = CVector(1.0f, 0.0f, 0.0f)*mMatrixRotate;
	CVector vy = CVector(0.0f, 1.0f, 0.0f)*mMatrixRotate;
	CVector vz = CVector(0.0f, 0.0f, 1.0f)*mMatrixRotate;
	CTransform::Update();
	//mPosition = CVector(0.0f, 0.0f, 0.9f)*mMatrix;


}

void COver::Collision(CCollider*m, CCollider*o){
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
					//CFriendly::spInstance->mHp = 0;
				}
			}
		}
		return;
	}
	switch (o->mType)
	{
	case CCollider::ESPHERE:
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
void COver::TaskCollision()
{
	mCollider.ChangePriority();

	//Õ“Ëˆ—‚ÌŽÀs
	CCollisionManager::Get()->Collision(&mCollider, COLLSIONRANGE);
	mColSearch.ChangePriority();
	CCollisionManager::Get()->Collision(&mColSearch, COLLSIONRANGE);
}
