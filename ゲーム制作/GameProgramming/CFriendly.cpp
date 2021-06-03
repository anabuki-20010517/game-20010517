#include"CFriendly.h"
#include"CEffect.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"
#include"CBullet.h"
#define OBJ "f16.obj"
#define MTL "f16.mtl"
#define HP 3
CModel CFriendly::mModel;

CFriendly::CFriendly()
:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4f)
, mColSearch(this, &mMatrix, CVector(0.0f, 0.0f, 100.0f), 30.0f)
, mpPlayer(0)
, mHp(HP)
{
	if (mModel.mTriangles.size() == 0)
	{
		mModel.Load(OBJ, MTL);
	}
	mpModel = &mModel;
	mColSearch.mTag = CCollider::ESEARCH;
}

CFriendly::CFriendly(const CVector&position, const CVector&rotation,
	const CVector&scale)
	: CFriendly()
{
	mPosition = position; //�ʒu
	mRotation = rotation; //��]
	mScale = scale;		  //�g�k
	CTransform::Update(); //�s��
	mPriority = 1;
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);

}
void CFriendly::Update(){
	CVector vx = CVector(1.0f, 0.0f, 0.0f)*mMatrixRotate;
	CVector vy = CVector(0.0f, 1.0f, 0.0f)*mMatrixRotate;
	CVector vz = CVector(0.0f, 0.0f, 1.0f)*mMatrixRotate;
	if (mpPlayer)
	{
		CVector vp = mpPlayer->mPosition - mPosition;
		float dx = vp.Dot(vx);
		float dy = vp.Dot(vy);
		float dz = vp.Dot(vz);
		//X���̃Y����2.0�ȉ�
		if (-2.0f < dx && dx < 2.0f)
		{
			//Y���̃Y����2.0�ȉ�
			if (-2.0f < dy && dy < 2.0f)
			{
				if (0.0f< dz){
					CBullet*bullet = new CBullet();
					bullet->Set(0.1f, 1.5f);
					bullet->mPosition = CVector(0.0f, 0.0f, 10.0f)*mMatrix;
					bullet->mRotation = mRotation;
					bullet->Update();
				}
			}
		}
	}
	mpPlayer = 0;
	if (mHp <= 0)
	{
		mHp--;
		//15�t���[�����ɃG�t�F�N�g
		if (mHp % 15 == 0)
		{
			new CEffect(mPosition, 1.0f, 1.0f, "exp.tag", 4, 4, 2);
		}
		mPosition.mY -= 0.03f;
		CTransform::Update();
		return;
	}
	//CTransform::Update();
	//mPosition = CVector(0.0f, 0.0f, 0.9f)*mMatrix;
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
			if (o->mpParent->mTag == EPLAYER)
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

	//�Փˏ����̎��s
	CCollisionManager::Get()->Collision(&mCollider, COLLSIONRANGE);
	mColSearch.ChangePriority();
	CCollisionManager::Get()->Collision(&mColSearch, COLLSIONRANGE); 
}