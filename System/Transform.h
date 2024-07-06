#pragma once
#include "SystemBase.h"

namespace Engine
{
	namespace Component
	{
		class Transform;
	}

	namespace System
	{
		class Transform : public SystemBase
		{
		public:
			Transform() {}
			~Transform() {}
		public:
			bool Initialize(const std::vector<Entity::Entity*>* _entities) override;
			void Finalize() override
			{
			}
			void SetEntity(Entity::Entity* _entity) override;
			Entity::Entity* GetCamera() { return m_pCamera; }

		public:
			void FixedUpdate() override;
			void Update() override
			{
			}

		private:
			std::vector<std::vector<Component::Transform*>> m_TransformContainer;
			Entity::Entity* m_pCamera;
		};
	}
}