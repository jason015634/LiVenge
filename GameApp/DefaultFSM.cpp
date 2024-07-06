#include "DefaultFSM.h"
#include "../Component/FSM.h"
#include "Entity.h"


void DefaultFSM::Initialize()
{
	m_pBattleInfo = m_pOwner->GetEntity()->GetComponent<BattleInfo>();
}
