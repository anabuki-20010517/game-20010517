#include"CCharacter.h"
#include"CTaskManager.h"
CCharacter::CCharacter()
:mTag(EZERO)
{
	CTaskManager::Get()->Add(this);
}
CCharacter::~CCharacter(){
	CTaskManager::Get()->Remove(this);
}

void CCharacter::Render()
{
	mpModel->Render(mMatrix);
}
