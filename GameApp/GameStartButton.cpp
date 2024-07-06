#include "GameStartButton.h"

void GameStartButton::Initialize()
{
	__super::Initialize();

	AddComponent<Engine::Component::GameObject>()->SetTag(L"GameStartButton");
	GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_Start_Button.png");
	GetComponent<Engine::Component::UI>()->SetLayer(1);
	GetComponent<Engine::Component::UI>()->SetCameraAffect(false);
	//GetComponent<Engine::Component::Transform>()->SetScale(0.6, 0.7, 1);
	GetComponent<Engine::Component::Transform>()->m_Position.X = 1750.f;
	//GetComponent<Engine::Component::Transform>()->m_Position.X = 1750.f;
	GetComponent<Engine::Component::Transform>()->m_Position.Y = 60.0f;
	//GetComponent<Engine::Component::Transform>()->m_Position.Y = 30.0f;
}
