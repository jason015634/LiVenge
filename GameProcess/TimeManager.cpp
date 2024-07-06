#include "pch.h"
#include "TimeManager.h"

Engine::TimeManager::TimeManager()
{
	
}

bool Engine::TimeManager::Initialize()
{
	m_CurrTime = m_PrevTIme = GetTickCount64();
	m_DeltaTime = 0;
	return true;
}

void Engine::TimeManager::Finalize()
{
}

void Engine::TimeManager::Update()
{
	m_CurrTime = GetTickCount64();
	m_DeltaTime = m_CurrTime - m_PrevTIme;
	m_PrevTIme = m_CurrTime;
}
