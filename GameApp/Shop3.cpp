#include "Shop3.h"

void Shop3::Initialize()
{
	AddComponent<Engine::Component::GameObject>()->SetTag(L"Shop3");
	AddComponent<Engine::Component::UI>();
	//AddComponent<Engine::Component::Rectangle>()->SetLayer(0);
	//AddComponent < Engine::Component::Rectangle>()->SetRect(960, 154);
	//GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
	AddComponent<Engine::Component::Transform>();
	GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_store_level_3_image.png");
	GetComponent<Engine::Component::UI>()->SetLayer(1);
	GetComponent<Engine::Component::UI>()->SetCameraAffect(true);
	GetComponent < Engine::Component::Transform>()->m_Position.X = 675.0f;
	GetComponent < Engine::Component::Transform>()->m_Position.Y = 1555.0f;
}
