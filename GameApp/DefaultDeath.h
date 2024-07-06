#pragma once
#include "../Component/FSMState.h"

class DefaultDeath : public Engine::Component::FSMs::FSMState
{
public:
	DefaultDeath(Engine::Component::FSMs::FiniteStateMachine* _owner) :
		Engine::Component::FSMs::FSMState(_owner, L"Death")
	{

	}
	void Enter() override;
	void Logic() override;
	void Exit() override;

	virtual bool CheckTransition(std::wstring& NextState) override;
};

