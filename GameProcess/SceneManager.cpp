#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "../Component/ComponentList.h"

#include <iostream>

bool Engine::SceneManager::Initialize()
{
	m_SceneContainer.clear();
	return true;
}

bool Engine::SceneManager::Start(std::wstring _SceneName)
{
	auto iter = m_SceneContainer.find(_SceneName);

	if (iter == m_SceneContainer.end())
	{
		// Error
		assert(0);
		std::cout << m_pScene->GetNextScene().c_str() << " is Not Registed Scene!";
		return false;
	}

		//delete m_pScene;
		m_pScene = nullptr;

		m_pScene = iter->second;
		m_pScene->Initialize();
		m_Entities = m_pScene->GetHierarchyEntity();
		m_pScene->Start();

		for (auto entity : *m_Entities)
		{
			for (auto script : *entity->GetScripteComponent())
			{
				script->Start();
			}
		}
		return true;
	
	return true;
}

void Engine::SceneManager::FixedUpdate()
{
	m_pScene->FixedUpdate();
	for (auto entity : *m_Entities)
	{
		//if (entity->GetActive() == false) return;
		for (auto script : *entity->GetScripteComponent())
		{
			script->FixedUpdate();
		}
	}
}

void Engine::SceneManager::Update()
{
	m_pScene->Update();
	for (auto entity : *m_Entities)
	{
		//if (entity->GetActive() == false) return;
		for (auto script : *entity->GetScripteComponent())
		{
			script->Update();
		}
	}
}

void Engine::SceneManager::LateUpdate()
{
	m_pScene->LateUpdate();

	for (auto entity : *m_Entities)
	{
		//if (entity->GetActive() == false) return;

		for (auto script : *entity->GetScripteComponent())
		{
			script->LateUpdate();
		}
	}
}

void Engine::SceneManager::Finalize()
{
	for (auto entity : *m_Entities)
	{
		for (auto script : *entity->GetScripteComponent())
		{
			script->Finalize();
		}
	}
	for (auto iter = m_SceneContainer.begin(); iter != m_SceneContainer.end(); iter++)
	{
		SAFE_DELETE(iter->second);
	}
}

bool Engine::SceneManager::RegisterScene(std::wstring _sceneName, Scene* _scene)
{
	auto iter = m_SceneContainer.find(_sceneName);
	if (iter == m_SceneContainer.end())
	{
		m_SceneContainer.insert({ _sceneName,_scene });
		return true;
	}
	else
	{
		// Error
		_ASSERT(0);
		std::cout << _sceneName.c_str() << " is Always Registed!";
	}
	return false;
}

std::vector<Engine::Entity::Entity*>* Engine::SceneManager::GetCreatedEntities()
{
	return m_pScene->GetCreatedEntities();
}

void Engine::SceneManager::SetCreateEntities()
{
	for (auto entity : *m_pScene->GetCreatedEntities())
	{
		m_Entities->push_back(entity);
	}
	m_pScene->GetCreatedEntities()->clear();
}

bool Engine::SceneManager::IsChangeScene()
{	
	if (m_pScene->IsSceneChanged() == false)
	{
		return false;
	}
	m_pScene->Finalize();
	for (auto entity : *m_Entities)
	{
		/*for (auto script : *entity->GetScripteComponent())
		{
			script->Finalize();
		}*/
		if (entity->AddComponent<Engine::Component::GameObject>()->GetTag() == L"Player")
		{
			continue;
		}
		//SAFE_DELETE(entity);
	}
	//m_Entities->clear();

	return Start(m_pScene->GetNextScene());
}
