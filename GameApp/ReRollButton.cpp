#include "ReRollButton.h"

void ReRollButton::Initialize()
{
	__super::Initialize();
	//AddComponent<Engine::Component::Rectangle>()->SetRect(102.5f, 35.0f);
	/*AddComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Aqua));
	GetComponent<Engine::Component::Rectangle>()->SetLayer(1);*/
	AddComponent<Engine::Component::GameObject>()->SetTag(L"ReRollButton");
	//GetComponent<Engine::Component::Collider>()->SetColliderInfo(102.5f, 35.0f);
	GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_reset_5_image.png");
	GetComponent<Engine::Component::UI>()->SetLayer(2);
	GetComponent<Engine::Component::UI>()->SetCameraAffect(true);
	GetComponent<Engine::Component::Transform>()->m_Position.X = -120.0f;
	GetComponent<Engine::Component::Transform>()->m_Position.Y = 1600.0f;
}
