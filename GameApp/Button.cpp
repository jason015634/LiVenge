#include "Button.h"

void Button::Initialize()
{
    AddComponent<Engine::Component::UI>();
    AddComponent<Engine::Component::Transform>();
    AddComponent<Engine::Component::Collider>();
}
