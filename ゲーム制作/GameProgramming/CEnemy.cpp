#include"CEnemy.h"
#include"CEffect.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"

CEnemy::CEnemy(CModel*model, CVector position, CVector rotation, CVector scale)
:mCollider1(this,&mMatrix, CVector(0.0f,5.0f,0.0f),0.8f)
, mCollider2(this,&mMatrix, CVector(0.0f, 5.0f, 20.0f), 0.8f)
, mCollider3(this,&mMatrix, CVector(0.0f, 5.0f, -20.0f), 0.8f)

{
	mPriority = 1;
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
}
void CEnemy::Update(){
	CTransform::Update();
	mPosition = CVector(0.0f, 0.0f, 0.9f)*mMatrix;
}
//Õ“Ëˆ—
void CEnemy::Collision(CCollider*m, CCollider*o){
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}
	switch (o->mType)
	{
		case CCollider::ESPHERE:
	
			if (CCollider::Collision(m, o)){
				new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
				mEnabled = false;
			}
			break;
		case CCollider::ETRIANGLE:
			CVector adjust;
			if (CCollider::CollidionTriangleSphere(o,m,&adjust))
			{
				mPosition = mPosition + adjust;
			}
			break;
	}
}
void CEnemy::TaskCollision()
{
	mCollider1.ChangePriority();
	mCollider2.ChangePriority();
	mCollider3.ChangePriority();
	//Õ“Ëˆ—‚ÌŽÀs
	CCollisionManager::Get()->Collision(&mCollider1, COLLSIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider2, COLLSIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider3, COLLSIONRANGE);
}