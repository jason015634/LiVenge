#pragma once
#include "framework.h"

namespace Engine
{
	namespace Entity
	{
		class Entity;
	}
	namespace Component
	{
		class Base
		{
		public:
			Base() {}
			virtual ~Base() {}

		public:
			bool GetActive()
			{
				return m_bComponentActive;
			}
			void SetActive(bool _active)
			{
				m_bComponentActive = _active;
			}

			void SetEntity(Entity::Entity* _owner)
			{
				if (m_pOwner == nullptr)
				{
					m_pOwner = _owner;
				}
				else
				{
					// todo : 오류 출력
				}
			}

			Entity::Entity* GetEntity()
			{
				if (m_pOwner != nullptr)
				{
					return m_pOwner;
				}
				return nullptr;
			}


		private:
			bool m_bComponentActive = true;
			Entity::Entity* m_pOwner = nullptr;
		};
	}
}