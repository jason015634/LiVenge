#pragma once
#include "SystemBase.h"
#include "framework.h"

namespace Engine
{
	namespace Component
	{
		class Collider;
	}


	namespace System
	{
		class D2DRenderer;
		class Collider : public SystemBase
		{
		public:
			Collider(POINT* _point, D2DRenderer* _render) :
				m_pMousePosition(_point),
				m_pRenderer(_render)
			{}
			~Collider() {}
		public:
			bool Initialize(const std::vector<Entity::Entity*>* _entities) override;
			void Finalize() override
			{
			}
			void SetEntity(Entity::Entity* _entity) override;

			void SetBitmapCollider();

			bool MouseAABB();
			bool ScreenAABB();
		private:
			D2DRenderer* m_pRenderer;
			std::vector<std::pair<Component::Transform*, Component::Collider*>> m_Container;
			std::vector<std::pair<Component::Camera*, Component::Collider*>> m_CameraContainer;
			std::vector<std::pair<Component::UI*, Component::Collider*>> m_BitmapContainer;

			POINT* m_pMousePosition;

		public:
			void Update() override;
		};
	}
}