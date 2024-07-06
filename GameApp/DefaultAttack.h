#pragma once
#include "../Component/FSMState.h"

class DefaultAttack : public Engine::Component::FSMs::FSMState
{
public:
	DefaultAttack(Engine::Component::FSMs::FiniteStateMachine* _owner) :
		Engine::Component::FSMs::FSMState(_owner, L"Attack")
	{

	}
	void Enter() override;
	void Logic() override;
	void Exit() override;

	virtual bool CheckTransition(std::wstring& NextState) override;
};

