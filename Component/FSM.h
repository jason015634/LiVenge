#pragma once
#include "Component.h"
#include "FiniteStateMachine.h"

namespace Engine
{
	namespace Component
	{
		class FSM : public Component
		{
		public:
			FSM()
			{}
			virtual ~FSM()
			{
				if (m_pFiniteStateMachine != nullptr)
				{
					delete (m_pFiniteStateMachine);
				}
			}

		public:
			FSMs::FiniteStateMachine* m_pFiniteStateMachine;

		public:
			template<class T>
			T* CreateFiniteStateMachine()
			{
				_ASSERT(m_pFiniteStateMachine == nullptr);
				bool bIsBase = std::is_base_of<FSMs::FiniteStateMachine, T>::value;
				_ASSERT(bIsBase == true);
				T* instance = new T();

				m_pFiniteStateMachine = instance;
				instance->m_pOnwer = this;
				return instance;
			}
		public:
			static const int ComponentType = (int)E_ComponentType::FSM;
			static const ULONGLONG ComponentFlag = 0x01 << ComponentType;
		};
	}
}