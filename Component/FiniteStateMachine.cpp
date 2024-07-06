#include "pch.h"
#include "FiniteStateMachine.h"
#include "FSMState.h"

void Engine::Component::FSMs::FiniteStateMachine::ChangeState(std::wstring _stateName)
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Exit();
	}

	auto it = m_pStates.find(_stateName);
	if (it != m_pStates.end())
	{
		m_pCurrentState = it->second;
		// Enter Action
		// State가 변경될때 새로운 State가 시작 처리할 내용을 실행한다.
		m_CurrStateName = m_pCurrentState->GetName();
		m_pCurrentState->Enter();
	}
	else
	{
		// error
		_ASSERT(0);
	}
}

void Engine::Component::FSMs::FiniteStateMachine::SetIdleState(std::wstring _stateName)
{
	auto it = m_pStates.find(_stateName);
	if (it != m_pStates.end())
	{
		m_pIdleState = it->second;
	}
	else
	{
		// error
		_ASSERT(0);
	}
}

void Engine::Component::FSMs::FiniteStateMachine::AddState(FSMState* _state)
{
	m_pStates.insert({ _state->GetName(),_state });
}

void Engine::Component::FSMs::FiniteStateMachine::AddStateAlias(FSMStateAlias* _stateAlias)
{
	m_pStateAlias.push_back(_stateAlias);
}
