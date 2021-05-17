#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
#include"CTask.h"
class CTaskManager{
private:
	//タスクマネージャーのインスタンス
	static CTaskManager*mpInstance;
protected:
	//デフォルトコンストラクタ
	CTaskManager();
public:
	//インスタンスの取得
	static CTaskManager*Get();

	CTask mHead;//先頭タスク
	CTask mTail;//最終タスク

	virtual~CTaskManager();
	//Add(タスクのポインタ)
	void Add(CTask*addTask);
	void Update();
	void Render();
	//リストから削除
	void Remove(CTask*task);
	void Delete();
	void TaskCollision();
};

#endif