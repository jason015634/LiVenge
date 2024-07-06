#pragma once
#include "framework.h"

namespace Engine
{
	namespace Component
	{
		namespace FSMs
		{
			class FSMState;
			class FiniteStateMashine;
			class FSMTransition;

			class FSMStateAlias
			{
			public:
				FSMStateAlias(FiniteStateMashine* _owner) :
					m_pOwner(_owner)
				{}
				virtual ~FSMStateAlias() {};
			public:
				bool CheckAlias(FSMState* _state);
				bool CheckTransition(std::wstring& _OutNextState);
				void BindState(FSMState* _state);
				void BindTransition(FSMTransition* _transition);

			protected:
				FiniteStateMashine* m_pOwner;
			private:
				std::vector<FSMTransition*> m_Transitions;
				std::vector<FSMState*> m_States;
			};

		}
	}
}

