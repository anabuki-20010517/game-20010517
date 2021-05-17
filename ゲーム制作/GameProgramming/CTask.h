#ifndef CTASK_H
#define CTASK_H
class CTask{
public:
	CTask*mpNext;//次のポインタ
	CTask*mpPrev;//前のポインタ
	int mPriority; //優先度
	bool mEnabled; //有効フラグ
	CTask()
		:mpNext(0), mpPrev(0), mPriority(0), mEnabled(true){}
	virtual ~CTask(){}
	virtual void Update(){}
	virtual void Render(){}
	virtual void TaskCollision(){}
};
#endif