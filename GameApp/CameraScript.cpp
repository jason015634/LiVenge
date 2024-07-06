#include "CameraScript.h"
#include "../GameProcess/SingletonManager.h"

void CameraScript::Update()
{
	// Ä«¸Þ¶ó¶û ¸¶¿ì½º ÁÂÇ¥ ScreenScrollAABB
	/*if (GetEntity()->GetComponent<Engine::Component::Collider>()->ScreenScrollAABB(Engine::InputManager::GetInstance()->GetMousePos()->x, Engine::InputManager::GetInstance()->GetMousePos()->y) == 1)
	{
		GetEntity()->GetComponent<Engine::Component::Transform>()->m_Position.X -= 2.0;
	}*/
	if (GetEntity()->GetComponent<Engine::Component::Collider>()->ScreenScrollAABB(Engine::SingletonManager::GetInstance()->m_Input.GetMousePos()->x, Engine::SingletonManager::GetInstance()->m_Input.GetMousePos()->y) == 2)
	{
		if (GetEntity()->GetComponent<Engine::Component::Transform>()->m_Position.Y < - 400.f)
		{
			GetEntity()->GetComponent<Engine::Component::Transform>()->m_Position.Y -= 0.0f;
		}
		else
			GetEntity()->GetComponent<Engine::Component::Transform>()->m_Position.Y -= 4.0;
	}
	/*if (GetEntity()->GetComponent<Engine::Component::Collider>()->ScreenScrollAABB(Engine::InputManager::GetInstance()->GetMousePos()->x, Engine::InputManager::GetInstance()->GetMousePos()->y) == 3)
	{
		GetEntity()->GetComponent<Engine::Component::Transform>()->m_Position.X += 2.0;
	}*/
	if (GetEntity()->GetComponent<Engine::Component::Collider>()->ScreenScrollAABB(Engine::SingletonManager::GetInstance()->m_Input.GetMousePos()->x, Engine::SingletonManager::GetInstance()->m_Input.GetMousePos()->y) == 4)
	{
		if (GetEntity()->GetComponent<Engine::Component::Transform>()->m_Position.Y > 679.f)
		{
			GetEntity()->GetComponent<Engine::Component::Transform>()->m_Position.Y += 0.0f;
		}
		else
		GetEntity()->GetComponent<Engine::Component::Transform>()->m_Position.Y += 4.0;
	}
}
