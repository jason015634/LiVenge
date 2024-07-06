#pragma once
#include "framework.h"

namespace Engine
{
	namespace Component
	{
		namespace FSMs
		{
			class FiniteStateMachine;
			class FSMTransition
			{
			public:
				FSMTransition(FiniteStateMachine* _owner, std::wstring _nextState) :
					m_pOwner(_owner),
					m_NextState(_nextState)
				{}
				virtual ~FSMTransition() {}

			public:
				// Á¶°Ç
				virtual bool CheckCondition() abstract;
				const std::wstring& GetNextState() { return m_NextState; }

			protected:
				FiniteStateMachine* m_pOwner;
			private:
				std::wstring m_NextState;
			};
		}
	}
}
