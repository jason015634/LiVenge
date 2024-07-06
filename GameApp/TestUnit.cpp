#include "TestUnit.h"
#include "MouseDragging.h"

void TestUnit::Initialize()
{
	AddComponent<UnitStatus>();
	AddComponent<Engine::Component::Transform>()->SetPosition(0,0,0);
	AddComponent<Engine::Component::Render>()->SetBitmapPath(L"..\\Resource/test.png");
	AddComponent<Engine::Component::Collider>()->SetColliderRect(1000, 1000);
	AddComponent<Engine::Component::GameObject>()->SetTag(L"TestUnit");
	AddComponent<MouseDragging>();
}
