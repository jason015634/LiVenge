#include "DefaultIdle.h"
#include "DefaultFSM.h"



void DefaultIdle::Enter()
{
}

void DefaultIdle::Logic()
{
}

void DefaultIdle::Exit()
{
}

bool DefaultIdle::CheckTransition(std::wstring& NextState)
{
	DefaultFSM* pFSM = static_cast<DefaultFSM*>(m_pOwner);
	if (pFSM->m_pBattleInfo->GetAttackTarget().size() != 0)
	{
		NextState = L"Attack";
		return true;
	}
	else if (pFSM->m_pBattleInfo->GetMoveDistance().X != 0 && pFSM->m_pBattleInfo->GetMoveDistance().Y != 0)
	{
		NextState = L"Move";
		return true;
	}
	else if (pFSM->m_pBattleInfo->IsDead() == true)
	{
		NextState = L"Death";
		return true;
	}
	
	return false;
}
