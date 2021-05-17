#include"CCollider.h"
#include"CCollisionManager.h"
#include"CColliderLine.h"

CCollider::CCollider()
: mpParent(0)
, mpMatrix(&mMatrix)
, mType(ESPHERE)
, mTag(EBODY)
{
	CCollisionManager::Get()->Add(this);
}

CCollider::CCollider(CCharacter*parent, CMatrix*matrix, CVector position, float radius)
:CCollider()
{
	mpParent = parent;//親設定
	mpMatrix = matrix;//親行列設定
	//CTransform設定
	mPosition = position;//位置
	mRadius = radius;//半径設定
	//CCollisionManager::Get()->Add(this);
}
void CCollider::Render(){
	glPushMatrix();
	//コライダの中心座標計算
	//自分の座標x親の変換行列を掛ける
	CVector pos = mPosition**mpMatrix;
	//中心座標へ移動
	glMultMatrixf(CMatrix().Translate(pos.mX, pos.mY, pos.mZ).mM[0]);
	//DIFFUSE赤色設定
	float c[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//球描画
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();
}
CCollider::~CCollider(){
	CCollisionManager::Get()->Remove(this);
}
//衝突判定
bool CCollider::Collision(CCollider*m, CCollider*o){
	CVector mpos = m->mPosition**m->mpMatrix;
	CVector opos = o->mPosition**o->mpMatrix;
	mpos = mpos - opos;
	if (m->mRadius + o->mRadius > mpos.Length()){
		return true;
	}
	return false;
}
bool CCollider::CollisonTriangleLine(CCollider*t, CCollider*l, CVector*a){

	CVector v[3], sv, ev;
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;
	sv = l->mV[0] * *l->mpMatrix;
	ev = l->mV[1] * *l->mpMatrix;
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	CVector v0sv = sv - v[0];
	CVector v0ev = ev - v[0];
	float dots = v0sv.Dot(normal);
	float dote = v0ev.Dot(normal);
	if (dots*dote >= 0.0f){
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//面と線分の交点を求める
	CVector cross = sv + (ev - sv)*(abs(dots) / (abs(dots) + abs(dote)));
	//交点が三角形内なら衝突している
	//頂点1頂点2ベクトルと頂点1交点ベクトルとの外積求め
	//法線との内積がマイナスなら三角形の外
	if ((v[1] - v[0]).Cross(cross - v[0]).Dot(normal) < 0.0f){
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//頂点2頂点3ベクトルと頂点2交点ベクトルとの外積求め
	//法線との内積がマイナスなら三角形の外
	if ((v[2] - v[1]).Cross(cross - v[1]).Dot(normal) < 0.0f){
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//頂点3頂点1ベクトルと頂点3交点ベクトルとの外積求め
	//法線との内積がマイナスなら三角形の外
	if ((v[0] - v[2]).Cross(cross - v[2]).Dot(normal) < 0.0f){
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	if (dots < 0.0f){
		*a = normal*-dots;
	}
	else{
		*a = normal*-dote;
	}
	return true;
}

bool CCollider::CollidionTriangleSphere(CCollider*t, CCollider*s, CVector*a)
{
	CVector v[3], sv, ev;
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;

	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	sv = s->mPosition**s->mpMatrix + normal*s->mRadius;
	ev = s->mPosition**s->mpMatrix - normal*s->mRadius;
	CColliderLine line(NULL, NULL, sv, ev);
	return CollisonTriangleLine(t, &line, a);

}
void CCollider::ChangePriority()
{
	CVector pos = mPosition**mpMatrix;
	mPriority = pos.Length();
	CCollisionManager::Get()->Remove(this);
	CCollisionManager::Get()->Add(this);


}