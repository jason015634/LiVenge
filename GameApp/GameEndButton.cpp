#include "GameEndButton.h"

void GameEndButton::Initialize()
{
	__super::Initialize();
	GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_end_button.png");
	GetComponent<Engine::Component::UI>()->SetLayer(1);
	GetComponent<Engine::Component::Transform>()->SetPosition(1700, 100, 1);
}
