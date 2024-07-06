#pragma once
#include "framework.h"
#include "../Entity/Entity.h"

// 지워야함!
#include "../System/D2DRenderer.h"
#include "SingletonManager.h"

namespace Engine
{
	namespace System
	{
		class D2DRenderer;
	}

	class Scene
	{
	public:
		Scene() {}
		virtual ~Scene() {}

	public:
		std::vector<Entity::Entity*>* GetHierarchyEntity()
		{
			return &m_Entities;
		}
		std::vector<Entity::Entity*>* GetCreatedEntities()
		{
			return &m_CreateEntities;
		}

		const std::wstring& GetNextScene()
		{
			return m_NextScene;
		}
		bool IsSceneChanged()
		{
			return m_bSceneChanged;
		}
	protected:
		void ChangeScene(std::wstring _nextScene)
		{
			m_bSceneChanged = true;
			m_NextScene = _nextScene;
		}
		Engine::Entity::Entity* AddEntity(Engine::Entity::Entity* _entity)
		{
			if (_entity == nullptr) return nullptr;
			_entity->Initialize();
			m_Entities.push_back(_entity);
			return _entity;
		}
		Engine::Entity::Entity* CreateEntity(Engine::Entity::Entity* _entity)
		{
			if (_entity == nullptr) return nullptr;
			_entity->Initialize();
			m_CreateEntities.push_back(_entity);
			return _entity;
		}
	protected:
		SingletonManager* m_pTool = SingletonManager::GetInstance();

	private:
		std::vector<Entity::Entity*> m_Entities;
		std::vector<Entity::Entity*> m_CreateEntities;

	private:
		std::wstring m_NextScene = L"None";
		bool m_bSceneChanged = false;

	public:
		virtual void Initialize() abstract; 

		virtual void Start() abstract;
		virtual void FixedUpdate() abstract;
		virtual void Update() abstract;
		virtual void LateUpdate() abstract;

		virtual void Finalize() abstract;

	

	};
}
