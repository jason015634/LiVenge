#pragma once
#include "ComponentList.h"

class DefaultFSM : public Engine::Component::FSMs::FiniteStateMachine
{
public:
	DefaultFSM() {}
	~DefaultFSM() {}
public:
	void Initialize() override;

private:
	//state

public:
	BattleInfo* m_pBattleInfo;
};

