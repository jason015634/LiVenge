#include "HpBar.h"

void HpBar::Initialize()
{
	AddComponent<Engine::Component::GameObject>()->SetTag(L"HpBar");
	AddComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_HP_image.png");
	GetComponent<Engine::Component::UI>()->SetLayer(1);
	GetComponent<Engine::Component::UI>()->SetCameraAffect(false);
	AddComponent<Engine::Component::Transform>();
}


