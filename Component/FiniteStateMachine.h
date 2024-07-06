#pragma once
#include "framework.h"

namespace Engine
{
	namespace Component
	{
		class FSM;
		namespace FSMs
		{
			class FSMState;
			class FSMTransition;
			class FSMStateAlias;


			class FiniteStateMachine
			{
			public:
				FiniteStateMachine()
				{
				}
				virtual ~FiniteStateMachine() {}

			public:
				std::wstring m_CurrStateName;
				FSMState* m_pCurrentState = nullptr;	// ������� 
				FSMState* m_pIdleState = nullptr;		// �⺻����

				std::map<std::wstring, FSMState*> m_pStates; // ������ ���µ��� �����ϴ� �����̳�

				std::vector<FSMStateAlias*> m_pStateAlias;

				FSM* m_pOwner;

			public:
				virtual void Initialize() {};
				void ChangeState(std::wstring _stateName);
				void SetIdleState(std::wstring _stateName);
				void AddState(FSMState* _state);
				void AddStateAlias(FSMStateAlias* _stateAlias);



			};
		}

	}
}
