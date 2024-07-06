#pragma once
#include "../Component/FSMState.h"

class DefaultMove : public Engine::Component::FSMs::FSMState
{
public:
	DefaultMove(Engine::Component::FSMs::FiniteStateMachine* _owner) :
		Engine::Component::FSMs::FSMState(_owner, L"Move")
	{

	}
	void Enter() override;
	void Logic() override;
	void Exit() override;

	virtual bool CheckTransition(std::wstring& NextState) override;
};

