#pragma once
#include "framework.h"

namespace Engine
{
	namespace Component
	{
		namespace FSMs
		{
			class FSMTransition;
			class FiniteStateMachine;

			class FSMState
			{
			public:
				FSMState(FiniteStateMachine* _owner, std::wstring _name) :
					m_pOwner(_owner),
					m_Name(_name)
				{

				}

				virtual ~FSMState()
				{
				}
	
			public:
				const std::wstring& GetName() { return m_Name; }

				void AddTransition(FSMTransition* _transition)
				{
					m_Transitions.emplace_back(_transition);
				}
	
				virtual bool CheckTransition(std::wstring& _outNextState);
				virtual void Enter() abstract;
				virtual void Logic() {};
				virtual void Exit() abstract;

			private:
				std::wstring m_Name;

				std::vector<FSMTransition*> m_Transitions;

			protected:
				FiniteStateMachine* m_pOwner;

			};

		}
	}
}

