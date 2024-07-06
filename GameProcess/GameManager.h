#pragma once
#include "framework.h"

namespace Engine
{
	namespace System
	{
		class SystemBase;
		class RenderingSystem;
		class D2DRenderer;
		class Transform;
		class FSMSystem;
		class Collider;
	}

	class IManager;
	class SceneManager;
	class TimeManager;
	class InputManager;
	class Scene;

	class GameManager
	{
	public:
		GameManager();
		~GameManager() {};


	public:

		bool GameStart(std::wstring _sceneName);
		void RegisterScene(std::wstring _sceneName, Engine::Scene* _scene);

		friend class GameProcess;
	private:
		bool Initialize(HWND _hWnd, HINSTANCE _hInstance, int screenWidth = 0, int screenHeight = 0);
		void Finalize();

		void Physics();
		void Logic();
		void Render();
		bool Reset();

		void AddManager(IManager* _manager) { m_ManagerContainer.push_back(_manager); }
		System::SystemBase* AddSystem(System::SystemBase* _system) { m_SystemContainer.push_back(_system); return _system; }
	public:
		void AddCustumSystem(System::SystemBase* _system)
		{
			m_SystemContainer.push_back(_system);
		}

		void AddCustumPhsicsSystem(System::SystemBase* _system)
		{
			m_CustumPhysicsSystem.push_back(_system);
			m_SystemContainer.push_back(_system);
		}
		void AddCustumLogicSystem(System::SystemBase* _system)
		{
			m_CustumLogicSystem.push_back(_system);
			m_SystemContainer.push_back(_system);

		}
		void AddCustumRenderSystem(System::SystemBase* _system)
		{
			m_CustumRenderSystem.push_back(_system);
			m_SystemContainer.push_back(_system);

		}

		System::RenderingSystem* GetRenderSystem()
		{
			return m_pRenderingSystem;
		}
	private:
		// managers
		SceneManager* m_pSceneManager;
		// todo : 렌더 시스템으로 이동시킬것
		System::D2DRenderer* m_pRenderer;
		System::RenderingSystem* m_pRenderingSystem;
		System::Transform* m_pTransformSystem;
		System::FSMSystem* m_pFSMSystem;
		System::Collider* m_pColliderSystem;

		// container
		std::vector<IManager*> m_ManagerContainer;
		std::vector<System::SystemBase*> m_SystemContainer;

		std::vector<System::SystemBase*> m_CustumPhysicsSystem;
		std::vector<System::SystemBase*> m_CustumLogicSystem;
		std::vector<System::SystemBase*> m_CustumRenderSystem;


	private:
		HWND m_hWnd;
		HINSTANCE m_hInstance;

		double m_Progress = 0;
		double m_FPS = 1000 / 60;

	private:
		bool m_bIsGameStop = false;

	};
}


