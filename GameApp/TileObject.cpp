#include "TileObject.h"

void TileObject::Initialize()
{
	AddComponent<Tile>()->SetGridPos(px,py);
	AddComponent<Engine::Component::Rectangle>()->SetRect(75,75);
	GetComponent<Engine::Component::Rectangle>()->SetColor(color);
	AddComponent<Engine::Component::Collider>()->SetColliderInfo(75,75);
	AddComponent<Engine::Component::Transform>()->SetPosition((px*150),(py*150),0);
}
