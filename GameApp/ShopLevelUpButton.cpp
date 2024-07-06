#include "ShopLevelUpButton.h"

void ShopLevelUpButton::Initialize()
{
	__super::Initialize();
	//AddComponent<Engine::Component::Rectangle>()->SetRect(102.5f, 35.0f);
	/*AddComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Violet));
	GetComponent<Engine::Component::Rectangle>()->SetLayer(1);*/
	AddComponent<Engine::Component::GameObject>()->SetTag(L"ShopLevelUpButton");
	GetComponent<Engine::Component::Transform>()->m_Position.X = -120.0f;
	GetComponent<Engine::Component::Transform>()->m_Position.Y = 1500.0f;
	GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_levelup_20_image.png");
	GetComponent<Engine::Component::UI>()->SetLayer(2);
	GetComponent<Engine::Component::UI>()->SetCameraAffect(true);
}
