#ifndef CCHARACTER_H
#define CCHARACTER_H
#include"CTransform.h"
#include "CModel.h"
#include"CTask.h"
class CCollider;
class CCharacter :public CTransform,public CTask{
public:
	enum ETag
	{
		EZERO,			//初期値
		EPLAYER,		//プレイヤー
		EENEMY,			//敵
		EBULLETPLAYER,	//プレイヤー弾
		EBULLETENEMY,	//敵弾
	};
	ETag mTag;
	CModel*mpModel;
	void Render();
	~CCharacter();
	CCharacter();
	
	virtual void Collision(CCollider*m, CCollider*o){}
};

#endif