#pragma once
#include "../Component/FSMState.h"

class DefaultIdle : public Engine::Component::FSMs::FSMState
{
public:
	DefaultIdle(Engine::Component::FSMs::FiniteStateMachine* _owner) :
		Engine::Component::FSMs::FSMState(_owner, L"Idle")
	{

	}
	void Enter() override;
	void Logic() override;
	void Exit() override;

	virtual bool CheckTransition(std::wstring& NextState) override;
};

