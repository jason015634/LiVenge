#include "EditButton.h"

void EditButton::Initialize()
{
	__super::Initialize();
	GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_edit_button.png");
	GetComponent<Engine::Component::UI>()->SetLayer(1);
	GetComponent<Engine::Component::Transform>()->SetPosition(250, 100, 1);
}
