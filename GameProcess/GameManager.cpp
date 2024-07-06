#include "pch.h"
#include "GameManager.h"
#include "SceneManager.h"

#include "../System/SystemList.h"
#include "SingletonManager.h"

Engine::GameManager::GameManager()
{
}

bool Engine::GameManager::Initialize(HWND _hWNd, HINSTANCE _hInstance, int _screenWidth, int _screenHeight)
{
	m_hWnd = _hWNd;
	m_hInstance = _hInstance;

	m_pRenderer = new System::D2DRenderer();
	m_pSceneManager = new SceneManager();
	m_pRenderingSystem = new System::RenderingSystem(m_pRenderer);
	m_pTransformSystem = new System::Transform();

	AddManager(m_pSceneManager);

	AddSystem(m_pTransformSystem);
	AddSystem(new System::FSMSystem);
	AddSystem(new System::Collider( SingletonManager::GetInstance()->m_Input.GetMousePos(), m_pRenderer));
	AddSystem(m_pRenderingSystem);

	for (auto manager : m_ManagerContainer)
	{
		if (manager->Initialize() == false)
		{
			return false;
		}
	}

	// todo : 나중에 렌더 시스템으로 구현할것
	// 렌더 시스템은 다른 시스템들과 구별되는 시스템임
	return m_pRenderer->Initialize(m_hInstance, m_hWnd, _screenWidth, _screenHeight);
}

void Engine::GameManager::Finalize()
{
	SAFE_DELETE(m_pSceneManager);
	for (auto system : m_SystemContainer)
	{
		SAFE_DELETE(system);
	}

}

bool Engine::GameManager::GameStart(std::wstring _sceneName)
{
	// todo : 씬매니저 스타트후 시스템들 리셋
	bool result = m_pSceneManager->Start(_sceneName);
	Reset();
	return result;
}

void Engine::GameManager::Physics()
{
	// 게임 일시정지 버튼 또는 조건
	if (SingletonManager::GetInstance()->m_Input.IsKeyTap(KEY::SPACE))
	{

	}

	SingletonManager::GetInstance()->m_Input.SetMouseOffset(
		m_pTransformSystem->GetCamera()->GetComponent<Engine::Component::Transform>()->m_Position.X,
		m_pTransformSystem->GetCamera()->GetComponent<Engine::Component::Transform>()->m_Position.Y);
	m_Progress += SingletonManager::GetInstance()->m_Time.GetDeltaTime();
	while (m_Progress > m_FPS)
	{
		m_Progress -= m_FPS;
		m_pSceneManager->FixedUpdate();

		for (auto system : m_SystemContainer)
		{
			system->FixedUpdate();
		}
	}
}

void Engine::GameManager::Logic()
{
	// todo : 릴리즈 버전에서는 지워야함!
	std::string str;
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(m_hWnd, &mouse);
	str.append("mouseX : ");
	str.append(std::to_string(mouse.x));
	str.append(" mouseY : ");
	str.append(std::to_string(mouse.y));
	SetWindowTextA(GetActiveWindow(), (str.c_str()));


	for (auto system : m_SystemContainer)
	{
		system->Update();
	}
	for (auto system : m_CustumLogicSystem)
	{
		system->Update();
	}

	m_pSceneManager->Update();
}

void Engine::GameManager::Render()
{
	m_pSceneManager->LateUpdate();
	for (auto system : m_SystemContainer)
	{
		system->LateUpdate();
		for (auto entity : *m_pSceneManager->GetCreatedEntities())
		{
			system->SetEntity(entity);
		}
	}

	m_pRenderingSystem->Render(SingletonManager::GetInstance()->m_Time.GetDeltaTime());

	m_pSceneManager->SetCreateEntities();
	if (m_pSceneManager->IsChangeScene())
	{
		// 씬 바뀜
		Reset();
	}
}

bool Engine::GameManager::Reset()
{
	for (auto system : m_SystemContainer)
	{
		if (system->Initialize(m_pSceneManager->GetEntities()) == false)
		{
			return false;
		}
	}
	return true;
}

void Engine::GameManager::RegisterScene(std::wstring _sceneName, Engine::Scene* _scene)
{
	m_pSceneManager->RegisterScene(_sceneName, _scene);
}


