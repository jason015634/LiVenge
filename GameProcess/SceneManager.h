#pragma once
#include "framework.h"
#include "IManager.h"
// todo : 瘤况具窃
#include "../System/D2DRenderer.h"

namespace Engine
{
	namespace Entity
	{
		class Entity;
	}
	class Scene;

	class SceneManager : public IManager
	{
	public:
		SceneManager(System::D2DRenderer* _renderer) :
			m_pD2DRenderer(_renderer)
		{}
		SceneManager() {};
		~SceneManager() {};

	public:
		bool Initialize() override final;
		void Finalize() override final;
		bool RegisterScene(std::wstring _sceneName,Scene* _scene);
		std::vector<Entity::Entity*>* GetEntities() { return m_Entities; }
		std::vector<Entity::Entity*>* GetCreatedEntities();
		void SetCreateEntities();

	private:
		std::vector<Entity::Entity*>* m_Entities;

		std::map < std::wstring, Engine::Scene*> m_SceneContainer;
		Scene* m_pScene;
		// todo : 瘤况具窃
		System::D2DRenderer* m_pD2DRenderer;

	public:
		bool Start(std::wstring _sceneName);
		void FixedUpdate();
		void Update();
		void LateUpdate();
		bool IsChangeScene();
	};

}

