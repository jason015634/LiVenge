#include "ManaBar.h"

void ManaBar::Initialize()
{
	AddComponent<Engine::Component::GameObject>()->SetTag(L"ManaBar");
	AddComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_MP_image.png");
	GetComponent<Engine::Component::UI>()->SetLayer(1);
	GetComponent<Engine::Component::UI>()->SetCameraAffect(false);
	AddComponent<Engine::Component::Transform>();

}
