#include"CBullet.h"
#include"CCollisionManager.h"
CBullet::CBullet()
:mLife(50)
, mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.1f)
{}
void CBullet::Set(float w, float d){
	//スケール設定
	mScale = CVector(1.0f, 1.0f, 1.0f);
	mT.SetVertex(CVector(w, 0.0f,0.0f), CVector(0.0f, 0.0f,-d), CVector(-w, 0.0f,0.0f));
	//三角形の法線設定
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));
}
void CBullet::Update(){
	if (mLife-- > 0){
		CTransform::Update();
		mPosition = CVector(0.0f, 0.0f, 1.0f)*mMatrix;
	}
	else{
		mEnabled = false;
	}
}
void CBullet::Render(){
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	mT.Render(mMatrix);

}
void CBullet::Collision(CCollider*m, CCollider*o){
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}
	if (CCollider::Collision(m, o)){
		mEnabled = false;
	}
}
void CBullet::TaskCollision()
{
	mCollider.ChangePriority();

	//衝突処理の実行
	CCollisionManager::Get()->Collision(&mCollider, COLLSIONRANGE);
}