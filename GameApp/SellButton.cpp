#include "SellButton.h"

void SellButton::Initialize()
{
	__super::Initialize();
	AddComponent<Engine::Component::GameObject>()->SetTag(L"SellButton");
	GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_delete_image.png");
	GetComponent<Engine::Component::UI>()->SetLayer(2);
	GetComponent<Engine::Component::UI>()->SetCameraAffect(true);
	GetComponent<Engine::Component::Transform>()->SetPosition(-120.f, 1700.f);
}
