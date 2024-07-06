#pragma once
#include "SystemBase.h"
#include "framework.h"
namespace Engine
{
	namespace System
	{
		class UISystem : public SystemBase
		{
		public:
			UISystem() {}
			~UISystem() {}
		public:
			bool Initialize(const std::vector<Engine::Entity::Entity*>* _entities) override;
			void Finalize() override
			{
			}
			void SetEntity(Entity::Entity* _entity) override;

		private:
			std::vector<Component::UI*> m_UIContainer;

		public:
			void Update() override;
		};
	}
}


