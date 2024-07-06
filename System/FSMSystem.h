#pragma once
#include "SystemBase.h"

namespace Engine
{
	namespace Component
	{
		class FSM;
	}
	namespace System
	{
		class FSMSystem : public SystemBase
		{
		public:
			FSMSystem() {}
			~FSMSystem() {}

		public:
			bool Initialize(const std::vector<Entity::Entity*>* _entities) override;
			void Finalize() override;
			void SetEntity(Entity::Entity* _entity) override;

		private:
			template<typename T>
			void SetComponentsState(Entity::Entity* _pEntity, std::wstring _state);
			void ChangeState(Component::FSM* _pFSM, std::wstring _name);

		public:
			void Update() override;

		private:
			std::vector<Component::FSM*> m_FSMContainer;

		};
		template<typename T>
		inline void FSMSystem::SetComponentsState(Entity::Entity* _pEntity, std::wstring _state)
		{
			if ((_pEntity->GetComponentFlag() & T::ComponentFlag) == T::ComponentFlag)
			{
				_pEntity->GetComponent<T>()->SetState(_state);
			}
		}
	}
}