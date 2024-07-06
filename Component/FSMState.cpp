#include "pch.h"
#include "FSMState.h"
#include "FSMTransition.h"

bool Engine::Component::FSMs::FSMState::CheckTransition(std::wstring& _outNextState)
{
	for (auto transition : m_Transitions)
	{
		if (transition->CheckCondition() == true)
		{
			_outNextState = transition->GetNextState();
			return true;
		}
	}
	return false;
}
