#pragma once
#include "framework.h"
#include "../Entity/Entity.h"
#include "../Component/ComponentList.h"
#include "../GameProcess/SingletonManager.h"



namespace Engine
{

	namespace System
	{
		class SystemBase
		{
		public:
			SystemBase() {}
			virtual ~SystemBase() {}

		public:
			virtual bool Initialize(const std::vector<Entity::Entity*>* _entities) abstract;
			virtual void Finalize() abstract;

			virtual void SetEntity(Entity::Entity* _entity)
			{
				ULONGLONG flag = 0;
				
				if ((_entity->GetComponentFlag() & flag) == flag)
				{
					m_Entities.push_back(_entity);
				}
				
			}

		protected:
			std::vector<Entity::Entity*> m_Entities;
			std::vector<Entity::Entity*> m_DontDestroyEntities;

		public:
			virtual void FixedUpdate() {};
			virtual void Update() {};
			virtual void LateUpdate() {};
		};
	}
}