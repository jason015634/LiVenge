#include "pch.h"
#include "SingletonManager.h"

Engine::SingletonManager* Engine::SingletonManager::m_pInstance = nullptr;

void Engine::SingletonManager::Initialize(HWND _hWnd)
{
	m_hWnd = _hWnd;
	m_Input.Initialize(m_hWnd);
	m_Time.Initialize();
}

void Engine::SingletonManager::Finalize()
{
}

void Engine::SingletonManager::Update()
{
	m_Input.Update();
	m_Time.Update();
}
