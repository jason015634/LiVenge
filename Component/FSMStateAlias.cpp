#include "pch.h"
#include "FSMStateAlias.h"
#include "FSMState.h"
#include "FSMTransition.h"

bool Engine::Component::FSMs::FSMStateAlias::CheckAlias(FSMState* _state)
{
    for (auto& alias : m_States)
    {
        if (alias == _state)
        {
            return true;
        }
    }
    return false;
}

bool Engine::Component::FSMs::FSMStateAlias::CheckTransition(std::wstring& _OutNextState)
{
    for (auto transition : m_Transitions)
    {
        if (transition->CheckCondition() == true)
        {
            _OutNextState = transition->GetNextState();
            return true;
        }
    }

    return false;
}

void Engine::Component::FSMs::FSMStateAlias::BindState(FSMState* _state)
{
	m_States.push_back(_state);
}

void Engine::Component::FSMs::FSMStateAlias::BindTransition(FSMTransition* _transition)
{
    m_Transitions.push_back(_transition);
}
