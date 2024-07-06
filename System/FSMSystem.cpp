#include "pch.h"
#include "FSMSystem.h"
#include "../Component/ComponentList.h"
#include "../Component/FSMState.h"
#include "../Component/FSMStateAlias.h"
#include "../Component/FSMTransition.h"



bool Engine::System::FSMSystem::Initialize(const std::vector<Entity::Entity*>* _entities)
{
	m_Entities.clear();

	for (auto entity : *_entities)
	{
		SetEntity(entity);
	}
	return true;
}

void Engine::System::FSMSystem::Finalize()
{
}

void Engine::System::FSMSystem::SetEntity(Entity::Entity* _entity)
{
	
	ULONGLONG flag = 0;
	flag += Component::FSM::ComponentFlag;
	if ((_entity->GetComponentFlag() & flag) == flag)
	{
		m_Entities.push_back(_entity);
	}
	
}


void Engine::System::FSMSystem::ChangeState(Component::FSM* _FSM, std::wstring _name)
{
	_FSM->m_pFiniteStateMachine->ChangeState(_name);
	// 여기에 fsm으로 변화시킬 상태를 가진 컴포넌트들 추가
	SetComponentsState<Component::Animator>(_FSM->GetEntity(), _name);
}

void Engine::System::FSMSystem::Update()
{
	for (auto fsm : m_FSMContainer)
	{
		if (fsm->GetEntity()->GetActive() == false || fsm->GetActive() == false)
		{
			continue;
		}
		if (fsm->GetEntity()->GetActive() == false || fsm->GetActive() == false)
		{
			continue;
		}
		if (fsm->m_pFiniteStateMachine->m_pCurrentState == nullptr)
		{
			// 초기 상태 설정
			assert(fsm->m_pFiniteStateMachine->m_pIdleState != nullptr);
			fsm->m_pFiniteStateMachine->ChangeState(fsm->m_pFiniteStateMachine->m_pIdleState->GetName());

			continue;
		}
		std::wstring nextStateName;
		if (fsm->m_pFiniteStateMachine->m_pCurrentState->CheckTransition(nextStateName) == true)
		{
			ChangeState(fsm, nextStateName);

			continue;
		}

		for (auto stateAlias : fsm->m_pFiniteStateMachine->m_pStateAlias)
		{
			if (!stateAlias->CheckAlias(fsm->m_pFiniteStateMachine->m_pCurrentState))
			{
				continue;
			}

			if (stateAlias->CheckTransition(nextStateName) == true)
			{
				ChangeState(fsm, nextStateName);
				break;
			}
		}

	}
}
